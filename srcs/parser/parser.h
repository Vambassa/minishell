/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:56:47 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 21:18:23 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../../includes/minishell.h"

//sub_func
int		skip_space(char *line, int i);
int		ft_isspace_1(char c);

//main func
t_arg	*args_proc(t_mini *mini);

char	*lsat_pars(char *line, t_env *env);
t_cmd	*pars_cmd(t_mini *mini);

char	*ft_strjoin_joiner_str(char const *s1, char *con, char const *s2);

char	*find_in_env(t_env *env, char *key);
#endif