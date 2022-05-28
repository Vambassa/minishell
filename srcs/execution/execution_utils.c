/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:13:22 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/25 23:09:29 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_copy(t_env *env)
{
	int		row_count;
	int		i;
	char	**env_arr;

	if (!env)
		return (NULL);
	row_count = env_lstsize(env);
	env_arr = (char **)malloc(sizeof(char *) * (row_count + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env && i < row_count)
	{
		env_arr[i] = ft_strdup(env->line);
		i++;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

static int	open_with_rights(char *path, char type)
{
	int	fd;

	fd = -1;
	if (type == 'I')
		fd = open(path, O_RDONLY);
	else if (type == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == 'A')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error_message("opening file error", 1);
		exit(g_exit_code);
	}
	return (fd);
}

void	open_file(t_cmd *cmds)
{
	t_rdr	*redir;

	redir = cmds->redir;
	while (redir)
	{
		if (!ft_strcmp("<", redir->type))
			cmds->in = open_with_rights(redir->name, 'I');
		else if (!ft_strcmp(">", redir->type))
			cmds->out = open_with_rights(redir->name, 'O');
		else if (!ft_strcmp(">>", redir->type))
			cmds->out = open_with_rights(redir->name, 'A');
		redir = redir->next;
	}
}
