/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:26:00 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/22 18:55:27 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

#include "libft.h"
#include "ft_eval.h"

# define HT_SIZE 2048

typedef enum	e_binerr
{
	br_OK = 0,
	br_PERMDENIED = 1,
	br_NOTFOUND = 2,
	br_ISDIR = 3,
}				t_binerr;

//hashtable
int		exaccess(char *file);
void	ht_init(void);
int		ht_hash(char *path);
t_list	*ht_get(char *path);
t_list	*ht_getexec(char *path);
int 	ht_getvalue(char *path, t_cmd_tab *cmd);
void	ht_del(void);
int		ht_getfile(char **paths, t_cmd_tab *cmd);
void	ht_refreshall(char *path);
t_list	**ht_gget(void);
int		ht_addfile(char	**paths, char *exec);
char	*ht_getpath(char **path, char *exec);

#endif
