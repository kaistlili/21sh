/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:26:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/28 17:34:22 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

void	free_tab_bytes(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmdlst(t_command *command_lst)
{
	t_command *tmp;

	tmp = command_lst;
	while (command_lst != NULL)
	{
		if (command_lst->args != NULL)
			free_tab(command_lst->args);
		if (command_lst->process_env != NULL)
			free_tab(command_lst->process_env);
		tmp = command_lst->next;
		free(command_lst);
		command_lst = tmp;
	}
	return ;
}
