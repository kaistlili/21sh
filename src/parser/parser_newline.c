/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:39:13 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/24 16:00:31 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	expect_newline_lst(t_parser *parser)
{
	int ret;

	if (parser->current->type != NEWLINE)
		return (SYNERR);
	while (parser->current->type == NEWLINE)
	{
		if ((ret = next_token(parser)))
			return (ret);
	}
	return (0);
}

int	expect_linebreak_rdl(t_parser *parser)
{
	int ret;

	if (((ret = expect_newline_lst(parser)) != SYNERR)
		&& (ret))
		return (ret);
	if (parser->current->type == EOI)
	{
		if ((ret = request_new_line(parser->lx_state)))
			return (ret);
		return (next_token(parser));
	}
	return (0);
}

int	expect_linebreak(t_parser *parser)
{
	int ret;

	if ((ret = expect_newline_lst(parser)) != SYNERR)
		return (ret);
	return (0);
}
