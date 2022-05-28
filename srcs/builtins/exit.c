/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:12:29 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/28 21:12:25 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_exit_error(char *arg, char *str)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exit_code = 255;
	exit(g_exit_code);
}

int	define_exit_code(long long res, int sign)
{
	res = res * sign;
	while (res > 255)
		res = res % 256;
	if (sign == -1)
		res = 256 + res;
	return (res);
}

int	atoi_minishell(char *str)
{
	size_t		i;
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	i = ft_isspace((const char *)str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (i > 20)
			return (print_exit_error(str, "numeric argument required"));
	}
	if (i == 20 && (res != LLONG_MAX || (res * sign) != LLONG_MIN))
		return (print_exit_error(str, "numeric argument required"));
	ft_putendl_fd("exit", STDERR_FILENO);
	return (define_exit_code(res, sign));
}

void	exit_execute(char **cmds)
{
	int	num;

	num = count_args(cmds);
	if (num == 1)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(0);
	}
	else if (num == 2 && !str_isdigit(cmds[1]))
	{
		g_exit_code = atoi_minishell(cmds[1]);
		exit(g_exit_code);
	}
	else if (num >= 2 && str_isdigit(cmds[1]))
		print_exit_error(cmds[1], "numeric argument required");
	else if (num > 2 && !str_isdigit(cmds[1]))
	{
		g_exit_code = 1;
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return ;
	}
}
