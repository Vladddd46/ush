#pragma once
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <pwd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <string.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <ctype.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <setjmp.h>
#include <stdarg.h>

extern char **environ;

/* STRUCTURES */
// parser structure. each node represents one inputed command
//-separated by separator (NULL in case of no separators)
typedef struct s_parsed_blocks {
    int    id;
    char   **cmd_expr;
    char   *separator;
    int    builtin;
    struct s_parsed_blocks *next;
} t_parsed_blocks;

typedef struct s_node {
    char          *string;
    struct s_node *next;
} t_node;

// processes store
typedef struct s_proc {
    int           id;
    pid_t         pid;
    char          *proc_name;
    struct s_proc *next;
} t_proc;

// stack for checking balanced parantheses in input
typedef struct s_braces_stack {
    char brace;
    int  index;
    struct s_braces_stack *next;
} t_braces_stack;

// local enviroment
typedef struct s_local_env {
    char *var_name;
    char *var_value;
    // just in case
    char **other_data;

    struct s_local_env *next;
} t_local_env;

/* MAIN */
void mx_main2(char *cmd, t_proc **proc_list, t_local_env **local_env);
void  mx_shlvl_adder();
char  *mx_getting_input(t_local_env **local_env);

/* INPUT MODULE */
char *mx_input(struct termios orig_termios, t_local_env **local_env);
void mx_enable_raw_mode(struct termios orig_termios);
void mx_disable_raw_mode(struct termios orig_termios);
void mx_ctrl_d(char buff, struct termios orig_termios);
void mx_screen_update(char *input, char buff, t_local_env **local_env);
void mx_reallocation(char **input, int *index, int *size);
// balanced parentheses checker
int  mx_balanced_parentheses_checker(char *input);
void mx_push_front_brace(t_braces_stack **list, char brace, int index);
void mx_pop_back_brace_stack(t_braces_stack **list);

/* INPUT PREPROCESSER */
void mx_input_preprocessing(char **cmd_expression, t_proc **proc, t_local_env **local_env);
void mx_arguments_preprocessor(char **cmd);
// tilda
void mx_tilda_handler(char **cmd);
void mx_resolution_error(char *var_name);
void mx_home_replace(char **arg_splt);
void mx_pwd_replace(char **arg_splt);
void mx_oldpwd_replace(char **arg_splt);
void mx_tilda_and_user_name(char **arg_splt);
// variable substitution
void mx_variable_substitution(char **cmd, t_local_env **local_env);
int  mx_end_index_finder(char *str, int dollar_indx);
char *mx_env_value_get(char *str, int start_indx, int end_indx, t_local_env **local_env);
char *mx_str_edit(char *str, char *value, int indx1, int indx2);
// command substitution
void mx_cmd_substitution(char **cmd, t_proc **proc, t_local_env **local_env);
char *mx_exe(char **cmd_arr, t_proc **proc, t_local_env **local_env);
char *mx_subcmd_exe(char *expr, int start_indx, 
                    int end_indx, t_proc **proc, t_local_env **local_env);

/* PARSING MODULE */
int             mx_parse_error(char **input_arr);
char            *mx_space_prettier(char *input_str);
char            **mx_semicolon_divider(char *input);
char            **mx_divide_by_space(char *expression);
t_parsed_blocks *mx_expression_parse(char *expression);
t_parsed_blocks *mx_list_creator(char **separators, char **exp_div_by_space);
t_parsed_blocks *mx_create_parsed_blocks_node(char **cmd_expr,
                                              char *separator,
                                              int builtin, 
                                              int id);
void            mx_prs_blocks_push_back(t_parsed_blocks **list, 
                                        char **cmd_expr, 
                                        char *separator,  
                                        int builtin); 

/* EXECUTE MODULE */
int mx_execute(char **cmd_expression, t_proc **proc, t_local_env **local_env);
void mx_built_ins_launcher(char **cmd_expression, t_proc **proc, t_local_env **local_env);
int  mx_is_built_in(char *cmd);
int  mx_external(char **cmd_expression, t_proc **proc, char *path, t_local_env **local_env);
int  mx_executing(char **cmd_expression, char *path);
void mx_child_exit(int exe_status, char **cmd_expression);
char *mx_find_external_storage_path(char *external_name, char *path);

/* BUITIN`S */
int  mx_which_usage_err(char **cmd);
char *mx_which_flags_determine(char **cmd, int *arg_index);
void mx_which(char **cmd, t_local_env **local_env);
// |echo|
void mx_echo(char **cmd);
char *mx_arg_edit(char *old_arg, char *flags);
char mx_escape_char_determiner(char c);
void mx_edit_with_resolve_esc_ch(char *old_arg, char **edited_str, int *i, int *index);
int  mx_valid_is_flag(char *flag);
char *mx_flags_retriever(char **cmd);
int  mx_flags_end_index(char **cmd);
// |pwd|
void mx_pwd(char **cmd_expression, t_local_env **local_env);
int  mx_pwd_flag_determine(char **cmd_expression, char *flag);
// |cd|
void mx_cd(char **cmd_exp, t_local_env **local_env);
void mx_cwd_changer(t_local_env **local_env, char *new_cwd, char *old_cwd);
char mx_cd_flag_retriever(char **cmd_exp);
int  mx_wd_from_user_indx(char **cmd_exp);
int  mx_access_errors(char *newcwd);
void mx_flag_s_link_error(char *arg);

char *mx_dot_resolver(char *not_resolved_wd);
// |jobs|
void mx_jobs(t_proc *proc);
// |exit|
void mx_exit(char **cmd_expression);
// |fg|
void   mx_fg(char **command_expression, t_proc **proc);
void   mx_fg_execute(pid_t pid, t_proc **proc);
void   mx_no_job_found(char *str);
void   mx_no_such_job(char *str);
int    mx_no_current_job_err(t_proc *proc);
t_proc *mx_create_proc_node(pid_t pid, char *proc_name, int id);
void   mx_push_proc_front(t_proc **list, pid_t pid, char *proc_name);
// |env|
void mx_env(char **cmd, t_proc **proc, t_local_env **local_env);
void mx_print_env();
int  mx_invalid_option_checker(char **cmd);
void mx_env_exe(char **cmd, int binary_index, t_proc **proc, char *path, t_local_env **local_env);
void mx_option_requires_an_argument(char *option);
int  mx_binary_index_finder(char **cmd,   int start);
void mx_specified_vars_setter(char **cmd, int start);
void mx_specified_vars_unsetter(char **cmd, int start);
void mx_env_flag_u(char **cmd, t_proc **proc, t_local_env **local_env);
void mx_env_flag_i(char **cmd, t_proc **proc, t_local_env **local_env);
void mx_env_flag_p(char **cmd, t_proc **proc, t_local_env **local_env);
// |export|
void mx_export(char **cmd);
void mx_export_printer(void);
int  mx_not_valid_identifier_error(char *str, char **data);
char **mx_splitter(char *arg);
// |unset|
void mx_unset(char **cmd);
int  mx_error_not_enough_args(char **cmd_expr);
void mx_no_such_var_msg(char *name);
// color 
void mx_color(char **cmd_expression);
void mx_bgcolor(char **cmd_expression);
// prompt
void mx_prompt(char **cmd_expr, t_local_env **local_env);

/* LIBMX */
char *mx_file_to_str(const char *file);
char *mx_strtrim(const char *str);
char *mx_three_join(char *str1, char *str2, char *str3);
char *mx_strnew(int size);
int  mx_strlen(const char *s);
char *mx_strjoin(char *s1, char *s2);
char *mx_string_copy(char *str);
char *mx_strcpy(char *dst, const char *src);
int  mx_strcmp(const char *s1, const char *s2);
int  mx_strarr_size(char **arr);
char **mx_strarr_join(char **arr1, char **arr2);
void mx_quicksort_strarr(char **arr, int left, int right);
void mx_printstr(const char *s);
void mx_print_strarr(char **strarr);
char **mx_new_strarr(int number_of_str);
char *mx_link(char *file, struct stat sb);
char *mx_itoa(int number);
int  mx_is_in_arr(char *s, char c);
int  mx_getint_len (int num);
char *mx_copystr(char *str);
int  mx_char_in_arr_counter(char *arr, char c);
char **mx_strsplit(const char *s, char c);
char *mx_file_name_retriever(char *file_path);
void mx_printstr_n(char *str);
char *mx_strtrim(const char *str);
int  mx_is_directory(char *dir_name);
int  mx_strs_in_arr_index(char **source, char **arr);
char *mx_substr_retriever(char *src_str, int indx1, int indx2);
char **mx_str_to_arr(char *str, char delim);
int  mx_str_in_arr_index(char **arr, char *str);
char **mx_divide_arr_by_index(char **arr, int index1, int index2);
void mx_arr_freesher(char **arr);
int  mx_substr_index(char *str, char *sub);
int  mx_char_index(char *str, char c);
char *mx_arr_to_path(char **arr);
int  mx_is_alphadigit(char c);
char **mx_arr_copy(char **old_arr);
char *mx_str_realloc(char *str, int added_size);
char *mx_upper_to_lower(char *old_str);

/* MINI FUNCTIONS */
void   mx_signals_restore();
void   mx_signals_ignore();
void   mx_suspended_process_msg(char *str);
void   mx_command_not_found_msg(char *cmd_name);
void   mx_controlling_terminal_change(pid_t proc_id);
void   mx_free_strs(int num, ...);

/* LOCAL ENVIROMENT */
void mx_push_front_local_env(t_local_env **list, char *var_name, char *var_value, char **other_data);
char *mx_get_var_value(t_local_env **list, char *var_name);
void mx_local_var_value_resetter(t_local_env **local_env, char *var_name, char *new_value);

/* ERRORS */
void mx_too_many_arguments_error(char *builtin_name);
void mx_bad_option(char *option, char *builtin_name);



