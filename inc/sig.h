/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:46:48 by apeyret           #+#    #+#             */
/*   Updated: 2019/05/20 15:22:02 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>

typedef struct	s_signal
{
	int			sig;
	void		(*func)(int);
}				t_signal;

void			sigcatch(int sig);
void			resize(int sig);
void			nothing(int sig);
void			unsetsig(void);
void			setsig(void);
#endif
