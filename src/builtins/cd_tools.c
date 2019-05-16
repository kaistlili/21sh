/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:08:33 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 13:59:17 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		cd_error(int errnum, char *arg)
{
	if (errnum == 1)
		putstr_stderr("cd: Pathname too long");
	else if (errnum == 2)
		putstr_stderr("cd : no such file or directory: ");
	else if (errnum == 3)
		putstr_stderr("cd: permission denied: ");
	else if (errnum == 4)
		putstr_stderr("cd: HOME not set");
	else if (errnum == 5)
		putstr_stderr("cd: Not a directory: ");
	if (arg != NULL)
		putstr_stderr(arg);
	putstr_stderr("\n");
	return (0);
}

int		cd_dispatch_err(char *arg, char *curpath, int freep)
{
	int ret;

	if (arg == NULL)
		arg = curpath;
	if ((ret = path_access(curpath)) != 0)
		cd_error(ret, arg);
	if ((freep) && (curpath))
		free(curpath);
	return (ret);
}

void	update_env_pwd(char *pwd, char *curpath)
{
	if (pwd != NULL)
	{
		set_shell_env("OLDPWD", pwd, 1);
		set_shell_env("PWD", curpath, 1);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (pwd != NULL)
		{
			set_shell_env("PWD", pwd, 1);
			free(pwd);
		}
	}
}

char	*getoldpwd(void)
{
	char *oldpwd;

	oldpwd = get_env_value("OLDPWD");
	if (oldpwd == NULL)
		return ("\0");
	ft_printf("%s\n", oldpwd);
	return (oldpwd);
}

char	*handle_abs_path(char *pwd, char *curpath)
{
	char *tmp;

	tmp = curpath;
	curpath = ft_strjoin(pwd, curpath);
	ft_strdel(&tmp);
	if (!curpath)
		return (NULL);
	return (curpath);

}

