NAME		= minishell

SRCS		= srcs/builtins/builtin_utils.c srcs/builtins/cd.c srcs/builtins/echo.c \
				srcs/builtins/env.c srcs/builtins/exit.c srcs/builtins/export_utils.c \
				srcs/builtins/export.c srcs/builtins/pwd.c srcs/builtins/unset.c \
				srcs/environment/environment_utils.c srcs/environment/init_env.c \
				srcs/execution/builtin_check_exec.c srcs/execution/children_process.c \
				srcs/execution/define_path.c srcs/execution/execute_commands.c \
				srcs/execution/execution_utils.c srcs/execution/handle_heredoc.c \
				srcs/execution/parent_process.c srcs/execution/pipe_work.c \
				srcs/parser/args_proc.c srcs/parser/dollar.c srcs/parser/for_parser_cmd.c \
				srcs/parser/pars_cmd.c srcs/parser/parser.c srcs/parser/pars_input.c \
				srcs/parser/redirect.c srcs/parser/utils.c srcs/utils/args_utils.c \
				srcs/utils/shell_utils.c srcs/main.c srcs/signal.c \
				srcs/utils/cmds_utils.c srcs/utils/print_utils.c srcs/utils/shell_memory.c \
				srcs/parser/rdr_proc.c srcs/utils/define_shlvl.c


OBJS		= $(patsubst %.c,%.o,$(SRCS))
D_FILES		= $(patsubst %.c,%.d,$(SRCS))

LIB			= ./libft

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RDL			= -lreadline -L/Users/vambassa/.brew/Cellar/readline/8.1.2/lib/ -I/Users/vambassa/.brew/Cellar/readline/8.1.2/include

RM			= rm -rf

all:		$(NAME)

$(NAME):	$(OBJS)
			make -C $(LIB)
			$(CC) $(CFLAGS) $(OBJS) $(LIB)/libft.a -o $(NAME) $(RDL)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@ -MD

clean:
			make clean -C $(LIB)
			$(RM) $(OBJS) $(D_FILES)

fclean:		clean
			make fclean -C $(LIB)
			$(RM) $(NAME)

re:			fclean all

-include $(D_FILES)

.PHONY:		all clean fclean re test
