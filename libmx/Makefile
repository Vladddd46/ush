NAME	=	libmx.a
CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic) -g
SRCD	=	src
INCD	=	inc
OBJD	=	obj
INC		=	libmx.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC		=	mx_arr_copy.c\
	mx_arr_freesher.c\
	mx_arr_len.c\
	mx_arr_to_path.c\
	mx_char_in_arr_counter.c\
	mx_char_index.c\
	mx_copystr.c\
	mx_divide_arr_by_index.c\
	mx_file_to_str.c\
	mx_getint_len.c\
	mx_is_alphadigit.c\
	mx_is_directory.c\
	mx_is_in_arr.c\
	mx_itoa.c\
	mx_link.c\
	mx_new_strarr.c\
	mx_print_strarr.c\
	mx_printstr.c\
	mx_printstr_n.c\
	mx_quicksort_strarr.c\
	mx_str_in_arr_index.c\
	mx_str_realloc.c\
	mx_str_to_arr.c\
	mx_strarr_join.c\
	mx_strarr_size.c\
	mx_strcmp.c\
	mx_strcpy.c.c\
	mx_string_copy.c\
	mx_strjoin.c\
	mx_strlen.c\
	mx_strnew.c\
	mx_strs_in_arr.c\
	mx_strtrim.c\
	mx_substr_index.c\
	mx_substr_retriever.c\
	mx_three_join.c\
	mx_upper_to_lower.c\


SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install

install: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLG) -c $< -o $@ -I$(INCD)
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

clean:
	@rm -rf $(OBJD)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@rm -rf $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install