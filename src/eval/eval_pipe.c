/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/20 14:12:14 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include "sig.h"

static void		close_pipes(int pipes[2])
{
	if (pipes)
	{
		close(pipes[0]);
		close(pipes[1]);
	}
	else
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
}

static int		wait_pipe(pid_t last, t_cmd_tab *cmd)
{
	int status;

	close_pipes(NULL);
	waitpid(last, &status, WUNTRACED);
	while (waitpid(0, NULL, WUNTRACED) > 0)
		;
	cmd->exit_status = (int)WEXITSTATUS(status);
	return (0);
}

int				pipe_recursion(t_cmd_tab *to, t_cmd_tab *from)
{
	int pipes[2];
	int pid;

	if ((((to) && ((pipe(pipes) != 0))) || (pid = fork()) == -1))
		return (MEMERR);
	if (pid == 0)
	{
		if (to)
		{
			if (dup2(pipes[1], STDOUT_FILENO) == -1)
				return (PIPEFAIL);
			close_pipes(pipes);
		}
		spawn_in_pipe(from);
		close_pipes(NULL);
		exit_wrap(from->exit_status, from);
	}
	if (to)
	{
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			return (PIPEFAIL);
		close_pipes(pipes);
		return (pipe_recursion(to->next, to));
	}
	return (wait_pipe(pid, from));
}

int				eval_pipe(t_cmd_tab *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (pipe_recursion(cmd->next, cmd) == PIPEFAIL)
		{
			ft_dprintf(STDERR_FILENO, "PIPEFAIL");
			exit_wrap(cmd->exit_status, cmd);
		}
		while (cmd->next)
			cmd = cmd->next;
		exit_wrap(cmd->exit_status, cmd);
	}
	wait_wrapper(cmd, pid);
	return (0);
}

int				exec_pipeline(t_ast_node *tree)
{
	t_cmd_tab	*cmd_tab;
	int			ret;

	ret = 0;
	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if (cmd_tab->next)
		ret = eval_pipe(cmd_tab);
	else
		ret = spawn_command(cmd_tab);
	tree->exit_status = cmd_tab->exit_status;
	g_sh.status = tree->exit_status;
	free_cmd_tab_lst(cmd_tab);
	return (ret);
}
