/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:45:19 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/10 15:35:31 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strnjoin(char **s1, char *s2, int n)
{
	char	*str;
	int		len;

	if (!s2)
		return (NULL);
	len = ft_strlen(*s1);
	if (!(str = ft_strnew(len + n)))
		return (NULL);
	str = ft_strcpy(str, *s1);
	str = ft_strncat(str, s2, n);
	ft_strdel(s1);
	return (str);
}

int			get_next_line(const int fd, char **line)
{
	static char tmp[BUFF_SIZE + 1];
	char		buf[1];
	int			curs;

	curs = -1;
	if (fd < 0 || read(fd, buf, 0) == -1 || !line)
		return (-1);
	*line = NULL;
	while (42)
	{
		if (tmp[0])
			*line = ft_strnjoin(line, tmp, ft_strichr(tmp, '\n', 0));
		if (ft_strchr(tmp, '\n') || (!curs && tmp[0]))
		{
			ft_strcpy(tmp, &(tmp[ft_strichr(tmp, '\n', 1)]));
			return (2);
		}
		if (!curs)
			return ((*line && **line) ? 1 : 0);
		curs = read(fd, tmp, BUFF_SIZE);
		tmp[curs] = '\0';
	}
}
