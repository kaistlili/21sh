/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:37:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/29 15:24:31 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "sig.h"

extern t_rdl g_rdl;

t_signal g_sig[] =\
{
	{SIGHUP, &sigcatch},
	{SIGINT, &nothing},
	{SIGQUIT, &sigcatch},
	//{SIGILL, &sigcatch},
	{SIGTRAP, &sigcatch}, // ?
	//{SIGABRT, &sigcatch},
	{SIGEMT, &sigcatch}, // ?
	//{SIGFPE, &sigcatch},
	{SIGKILL, &sigcatch},
	//{SIGBUS, &sigcatch},
	//{SIGSEGV, &sigcatch},
	//{SIGSYS, &sigcatch},
	{SIGPIPE, &sigcatch},
	{SIGALRM, &sigcatch},
	{SIGTERM, &sigcatch},
	{SIGURG, &sigcatch},
	{SIGSTOP, &sigcatch},
	{SIGTSTP, &sigcatch},
	{SIGCONT, &sigcatch},
	//{SIGCHLD, &sigcatch},
	{SIGTTIN, &sigcatch},
	{SIGTTOU, &sigcatch},
	{SIGIO, &sigcatch},
	{SIGXCPU, &sigcatch},
	{SIGXFSZ, &sigcatch},
	{SIGVTALRM, &sigcatch},
	{SIGPROF, &sigcatch},
	{SIGWINCH, &resize},
	{SIGINFO, &sigcatch},
	{SIGUSR1, &sigcatch},
	{SIGUSR2, &sigcatch},
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
