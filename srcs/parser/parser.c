/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:10:46 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 17:51:13 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_mini *mini)
{
	if (!check_line(mini->input))
	{
		mini->args = args_proc(mini);
		mini->cmds = pars_cmd(mini);
	}
	return (0);
}

char	*ft_strjoin_joiner_str(char const *s1, char *con, char const *s2)
{
	char	*ret;
	size_t	size1;
	size_t	size2;

	size1 = 0;
	size2 = 0;
	if (!s1 || !con || !s2)
		return (NULL);
	ret = (char *) malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(con) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	while (s1[size2])
		ret[size1++] = s1[size2++];
	size2 = 0;
	while (con[size2])
		ret[size1++] = con[size2++];
	size2 = 0;
	while (s2[size2])
		ret[size1++] = s2[size2++];
	ret[size1] = '\0';
	return (ret);
}
