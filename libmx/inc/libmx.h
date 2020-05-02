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
