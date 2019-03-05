/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:00:46 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/05 18:01:34 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

int		fc_l(t_fc fc)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*beg;
	int		i;

	lst = gethst();
	if (!lst)
		return (0);
	if (fc.range[0])
	{
		beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
			lst = hst_getcmp(lst, fc.range[1]);
	}
	else
	{
		if ((int)lst->content_size / 10 - 10 < 0)
			beg = hst_getcmp(lst, "0");
		else
			beg = hst_getcmp(lst, ft_itoa((int)lst->content_size / 10 - 10));
	}
	if (!lst || !beg)
		return (0);
	if (ft_cisin(fc.opt, 'r'))
	{
		tmp = lst;
		lst = beg;
		beg = tmp;
	}
	i = lst->content_size / 10 - (beg->content_size / 10);
	i += (i < 0 ? -1 : 1);
	fc_print(fc, beg, i);
	return (0);
}

int		fc_e(t_fc fc)
{
	char	*file;
	t_list	*lst;
	t_list	*beg;
	int		i;

	i = 1;
	lst = gethst();
	beg = lst;
	if (fc.range[0])
	{
		beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
		{
			lst = hst_getcmp(lst, fc.range[1]);
			i = lst->content_size / 10 - beg->content_size / 10;
			i += (i < 0 ? -1 : 1);
			ft_printf("%d\n", i);
		}
	}
	if (!(file = fc_filename(beg, i)))
		return (1);
	fc_writelst(file, beg, i);
	run_editor(&fc, file);
	if (ft_cisin(fc.opt, 'e'))
	{
		run_command(fc_read(file));
		ft_strdel(&file);
	}
	unlink(file);
	return (0);
}


int		fc_le(t_fc fc)
{
	char	*file;
	t_list	*lst;
	t_list	*beg;
	int		i;

	i = 1;
	lst = gethst();
	beg = lst;
	if (fc.range[0])
	{
		beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
		{
			lst = hst_getcmp(lst, fc.range[1]);
			i = lst->content_size / 10 - beg->content_size / 10;
			i += (i < 0 ? -1 : 1);
			ft_printf("%d\n", i);
		}
	}
	if (!(file = fc_filename(beg, i)))
		return (1);
	fc_writelst(file, beg, i);
	run_command(fc_read(file));
	ft_strdel(&file);
	unlink(file);
	return (0);
}

int		fc_s(t_fc fc)
{
	t_list	*lst;

	lst = gethst();
	if (fc.range[0])
		lst = hst_getcmp(lst, fc.range[0]);
	if (!lst)
		return (0);
	ft_printf("%s\n", lst->content);
	run_command(ft_strdup(lst->content));
	return (0);
}
