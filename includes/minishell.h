/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:15:16 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 21:13:45 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <sys/syslimits.h>
# include <errno.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define NO 0
# define YES 1

int	g_exit_code;

typedef struct s_mini
{
	char			*input;
	struct s_env	*env;
	struct s_env	*env_copy;
	struct s_arg	*args;
	struct s_cmd	*cmds;
}					t_mini;

typedef struct s_env
{
	char			*line;
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_arg
{
	char			*arg_origin;
	int				redirect;
	struct s_arg	*next;
}				t_arg;

typedef struct s_cmd
{
	char			**command;
	int				in;
	int				out;
	int				pipe_fd[2];
	pid_t			pid;
	int				fork;
	struct s_rdr	*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_rdr
{
	char			*type;
	char			*name;
	struct s_rdr	*next;
}				t_rdr;

// shell memory
void	init_shell(t_mini *shell);
void	free_shell(t_mini *shell);
void	free_cmds(t_cmd	**cmds);
void	free_args(t_arg **args);

// execute commands
void	execute_commands(t_mini *shell, t_cmd *cmds);
int		check_if_builtin(char *cmd);
void	builtin_exec(t_mini *shell, t_cmd *cmd);
int		pipe_creator(t_cmd *cmds);
void	children_process(t_mini *shell, t_cmd *cmds, t_cmd *begin);
void	parent_process(t_cmd *begin);
void	open_file(t_cmd *cmds);
void	handle_heredoc(t_cmd *cmd);
char	**env_copy(t_env *env);
char	*find_path(t_mini *shell, char *line);
void	execute_cmd(t_mini *shell, t_cmd *cmds);

// environment functions
void	init_env(t_mini *shell, char **env);
void	init_export_env(t_mini *shell, char **env);
char	*define_env_value(char *env_var, char *key);
char	*define_env_key(char *env_var);
void	define_shell_level(t_mini *shell);
void	change_env_value(t_env *env, char *key, char *value);

//arg utils
t_arg	*args_lstnew(char *arg_str);
void	args_lstadd_back(t_arg	**list, t_arg *new);

//cmd utils
t_cmd	*cmds_lstnew(t_arg *args);
void	cmds_lstadd_back(t_cmd	**list, t_cmd *new);

// builtin utils
int		count_args(char **args);
int		str_isdigit(char *str);
char	*cd_find_key_value(t_env *env, char *key);
void	change_value_in_env(t_env *env, char *key, char *value);
int		env_lstsize(t_env *env);
int		str_find_chr(char *s, char c);
void	free_array(char **arr);
int		invalid_export_var(char *var);
void	print_export_vars(t_env *var);
int		key_in_env_vars(char *key, t_env *env);
void	change_env_value(t_env *env, char *key, char *value);
void	add_new_var(t_env **vars, t_env *new);
t_env	*create_mew_var(char *new_var);

// builtins
int		builtin_check_exec(char *cmd);
void	echo_execute(char **cmds);
void	pwd_execute(void);
void	export_execute(t_mini *shell, char **cmds);
void	env_execute(t_env *env);
void	exit_execute(char **cmds);
void	unset_execute(t_mini *shell, char **cmds);
void	sort_env_copy(t_env *env_copy);
void	cd_execute(t_mini *shell, char **cmds);

// builtin utils
int		count_args(char **args);
int		str_isdigit(char *str);
char	*cd_find_key_value(t_env *env, char *key);
void	change_value_in_env(t_env *env, char *key, char *value);
int		find_var_in_env(t_env *env, char *var);

// handle signals
void	handle_signals(void);
void	handle_blocking_signals(void);

void	*allocate_mem(int size);

// utils
int		skip_spaces(char *str);
int		print_error_message(char *err_mess, int exit_code);

char	*clean_space(char *str);
int		check_redirect(char **line);
int		check_line(char *line);

int		parser(t_mini *mini);
int		check_redirect(char **line);

//sub_func
int		skip_space(char *line, int i);
int		ft_isspace_1(char c);

//main func
t_arg	*args_proc(t_mini *mini);

char	*lsat_pars(char *line, t_env *env);
t_cmd	*pars_cmd(t_mini *mini);

t_rdr	*redirect_processing(t_arg **args);
t_arg	*args_proc(t_mini *shell);

void	args_lstdelnode(t_arg **args);

void	rl_replace_line(const char *text, int clear_undo);
int		print_unset_error(char *str);
#endif