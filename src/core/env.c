/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 23:11:31 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/04 21:22:10 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
/* maybe ft_varnamelen instead of strlen ?*/
size_t env_name_len(char *var)
{
	size_t len;

	len = 0;
	while ((*var) && (valid_env_char(*var)))
	{
		var++;
		len++;
	}
	return (len);
}

char	*varchr(char **env, char *var)
{
	int		count;
	int		len;

	if (!env || !var)
		return (NULL);
	count = 0;
	len = env_name_len(var);
	while (env[count])
	{
		if ((!ft_strncmp(env[count], var, len)) && (env[count][len] == '='))
			return (env[count] + len + 1);
		count++;
	}
	return (NULL);
}

char	*envchrr(char **env, char *var)
{
	int count;
	int len;

	if (!var || !env)
		return (NULL);
	len = ft_strlen(var);
	count = 0;
	while (env[count])
	{
		if (!ft_strncmp(env[count], var, len) && env[count][len] == '=')
			return (env[count] + len + 1);
		count++;
	}
	return (NULL);
}

char	**shlvl(char **env)
{
	char	*var;
	int		lvl;

	var = NULL;
	var = varchr(env, "SHLVL=");
	if (!var)
		lvl = 1;
	else
		lvl = ft_atoi(var) + 1;
	env = envaddint(env, "SHLVL", lvl);
	return (env);
}
