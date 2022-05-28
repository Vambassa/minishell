/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:53:01 by calecia           #+#    #+#             */
/*   Updated: 2022/03/21 20:49:05 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

static int	sub_func(char **line)
{
	while (**line && ft_isspace_1(**line))
	{
		(*line)++;
	}
	if (**line == '\0')
		return (print_error_message(
				"syntax error near unexpected token `newline'", 258));
	else if (**line == '|')
		return (print_error_message(
				"syntax error near unexpected token `|'", 258));
	else if (**line == '>')
		return (print_error_message(
				"syntax error near unexpected token `>'", 258));
	else if (**line == '<')
		return (print_error_message(
				"syntax error near unexpected token `<'", 258));
	else if (**line == ';')
		return (print_error_message(
				"syntax error near unexpected token `;'", 258));
	else
		return (0);
}

static int	redirect_write(char **line)
{
	(*line)++;
	if (**line == '\0' || **line == '|')
	{
		return (print_error_message(
				"syntax error near unexpected token `newline'", 258));
	}
	else if (**line == '<')
	{
		return (print_error_message(
				"syntax error near unexpected token `<'", 258));
	}
	else if (**line == '>')
	{
		(*line)++;
		return (sub_func(line));
	}
	else
	{
		return (sub_func(line));
	}
}

static int	redirect_read(char **line)
{
	(*line)++;
	if (**line == '\0' || **line == '>')
		return (print_error_message(
				"syntax error near unexpected token `newline'", 258));
	else if (**line == '|')
		return (print_error_message(
				"syntax error near unexpected token `|'", 258));
	else if (**line == '<')
	{
		(*line)++;
		return (sub_func(line));
	}
	else
	{
		return (sub_func(line));
	}
}

int	check_redirect(char **line)
{
	if (**line == '>' && redirect_write(line))
	{
		return (1);
	}
	else if (**line == '<' && redirect_read(line))
	{
		return (1);
	}
	return (0);
}
