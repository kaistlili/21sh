/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_move.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:15:40 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/12 21:31:11 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		np_word(t_rdl *rdl, int i)
{
	int count;
	
	count = 0;
	if ((i < 0 && rdl->curs) || (i > 0 && rdl->str[rdl->curs]))
		count++;
	while (rdl->curs +  i * count >= 0 && rdl->str[rdl->curs +  i * count]
		&& (rdl->str[rdl->curs +  i * count] == ' '
			|| rdl->str[rdl->curs +  i * count] == '\n'))
		count++;
	while (rdl->curs +  i * count >= 0 && rdl->str[rdl->curs +  i * count]
		&& rdl->str[rdl->curs +  i * count] != ' '
			&& rdl->str[rdl->curs +  i * count] != '\n')
		count++;
	if (rdl->curs + i * count < 0)
		count = rdl->curs + 1;
	if (count)
		count--;
	return (count);
}

int		next_word(t_rdl *rdl, char *buf)
{
	int count;

	(void)buf;
	count = np_word(rdl, 1);
	right(rdl, count);
	rdl->curs += count;
	return (0);
}

int		prev_word(t_rdl *rdl, char *buf)
{
	int count;
	
	(void)buf;
	count = np_word(rdl, -1);
	left(rdl, count);
	rdl->curs -= count;
	return (0);
}

int		begin(t_rdl *rdl, char *buf)
{
	(void)buf;
	left(rdl, rdl->curs);
	rdl->curs = 0;
	return (0);
}

int		move_curs(t_rdl *rdl, char *buf)
{
	if (!ft_strcmp(K_RGHT, buf) && rdl->size > rdl->curs)
	{
		right(rdl, 1);
		rdl->curs++;
	}
	if (!ft_strcmp(K_LEFT, buf) && rdl->curs > 0)
	{
		left(rdl, 1);
		rdl->curs--;
	}
	return (0);
}
