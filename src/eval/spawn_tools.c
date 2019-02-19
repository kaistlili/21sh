/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:20:53 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/19 18:23:44 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

void		exec_error(int errnum, char *str)
{
	if (errnum == BIN_NO_PATH)
		putstr_stderr("21sh: PATH not set");
	else if (errnum == CMD_NOT_FOUND)
		putstr_stderr("21sh: command not found: ");
	else if (errnum == BIN_PERM_DENY)
		putstr_stderr("21sh: permission denied: ");
	else if (errnum == BIN_NOT_FOUND)
		putstr_stderr("21sh: no such file or directory: ");
	else if (errnum == BIN_EXEC_ERR)
		putstr_stderr("21sh: exec error: ");
	else if (errnum == BIN_IS_DIR)
		putstr_stderr("21sh: is a directory: ");
	if (str != NULL)
		putstr_stderr(str);
	putstr_stderr("\n");
}

int			bin_perm(char *path)
{
	struct stat target;

	if (stat(path, &target) != 0)
		return (BIN_NOT_FOUND);
	if (!S_ISREG(target.st_mode))
	{
		if (S_ISDIR(target.st_mode))
				return (BIN_IS_DIR);
		return (BIN_PERM_DENY);
	}
	if (access(path, X_OK) != 0)
		return (BIN_PERM_DENY);
	return (0);
}

int			handle_perm(char *cmd_name)
{
	int ret;

	if ((ret = bin_perm(cmd_name)) != 0)
		return (ACCERR);
	return (0);
}

void	exit_wrap(int code, t_cmd_tab *cmd)
{	
//	free_cmd_tab(cmd); maybe this is where fork leaks ?
	exec_error(code, cmd->av[0]);	
	(void)cmd;
	exit(code);
}
