/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:14:03 by vambassa          #+#    #+#             */
/*   Updated: 2022/03/24 17:39:07 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error_message(char *err_mess, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(err_mess, STDERR_FILENO);
	g_exit_code = exit_code;
	return (EXIT_FAILURE);
}
