/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:13:42 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 18:27:26 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define ERROR2 "syntax error near unexpected token `;;'"
#define ERROR_PIPE2 "syntax error near unexpected token `||'"
#define ERROR_PIPE1 "syntax error near unexpected token `|'"
#define ERROR1 "syntax error near unexpected token `;'"

static int	check_double_pipe(const char *line)
{
	if (*(line) == ';')
	{
		if (*(line + 1) == ';')
			return (print_error_message(ERROR2, 258));
		return (print_error_message(ERROR1, 258));
	}
	if (*(line) == '|')
	{
		if (*(line + 1) == '|')
			return (print_error_message(ERROR_PIPE2, 258));
		return (print_error_message(ERROR_PIPE1, 258));
	}
	return (0);
}

static int	search_ch(char **line, char ch)
{
	(*line)++;
	while (**line)
	{
		if (**line == ch)
			return (0);
		(*line)++;
	}
	return (print_error_message("syntax error with unclosed quotes", 258));
}

int	check_line(char *line)
{
	if (!line)
		return (EXIT_FAILURE);
	if (*line == '|' || *line == ';')
		return (check_double_pipe(line));
	while (line && *line)
	{
		if ((*line == '|' || *line == ';') && check_double_pipe(line + 1))
			return (1);
		if ((*line == '\'') && search_ch(&(line), '\''))
			return (1);
		if ((*line == '\"') && search_ch(&(line), '\"'))
			return (1);
		if ((*line == '<' || *line == '>') && check_redirect(&line))
			return (1);
		line++;
	}
	return (0);
}
