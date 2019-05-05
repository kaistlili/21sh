/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:37:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/05/05 17:54:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "sig.h"

extern t_rdl g_rdl;

t_signal g_sig[] =\
{
	{SIGINT, &nothing},
	{SIGQUIT, &sigcatch},
	{SIGSTOP, &sigcatch},
	{SIGWINCH, &resize},
	{0, sigcatch}
};

void	resize(int sig)
{
	(void)sig;
	g_rdl.col = getcolumn();
	reprint(&g_rdl, g_rdl.curs);
}

void	sigcatch(int sig)
{
	ft_printf("Catch Signal: %d\n", sig);
}

void	nothing(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	setsig(void)
{
	int		i;

	i = 0;
	while (g_sig[i].sig)
	{
		signal(g_sig[i].sig, g_sig[i].func);
		i++;
	}
}

void	unsetsig(void)
{
	int		i;

	i = 0;
	while (g_sig[i].sig)
	{
		signal(g_sig[i].sig, SIG_DFL);
		i++;
	}
}
