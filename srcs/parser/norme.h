/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vambassa <vambassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:39:56 by calecia           #+#    #+#             */
/*   Updated: 2022/03/28 21:20:37 by vambassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORME_H
# define NORME_H

typedef struct s_norme
{
	int		i;
	int		start;
	int		end;
	int		flag;
	char	*temp;
}	t_norme;

#endif