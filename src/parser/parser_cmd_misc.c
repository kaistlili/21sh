/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_misc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:50:17 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/25 21:52:55 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	wrapper_free_cmd(int ret, t_parser *parser)
{
	free_simple_cmd(&(parser->cmd));
	return (ret);
}

int	expect_separator_op(t_parser *parser)
{
	int ret;

	if ((parser->current->type == AMPERS)
		|| (parser->current->type == SEMI_COL))
	{
		if ((ret = tree_add_sep(parser)))
			return (ret);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_separator(t_parser *parser)
{
	int ret;

	if (!(ret = expect_separator_op(parser)))
	{
		if ((ret = expect_linebreak(parser)) && (ret != SYNERR))
			return (ret);
		return (0);
	}
	else
		return (ret);
	if (!(ret = expect_newline_lst(parser)))
		return (0);
	return (ret);
}

int	expect_cmd_pre(t_parser *parser)
{
	int ret;

	if (((ret = expect_io_redir(parser)) != SYNERR)
		|| ((ret = expect_assign(parser)) != SYNERR))
	{
		if (ret)
			return (ret);
		if (((ret = expect_cmd_pre(parser)) != SYNERR) && (ret))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_cmd_suffix(t_parser *parser)
{
	int ret;

	if (((ret = expect_io_redir(parser)) != SYNERR)
		|| ((ret = expect_word(parser)) != SYNERR))
	{
		if (ret)
			return (ret);
		if (((ret = expect_cmd_suffix(parser)) != SYNERR) && (ret))
			return (ret);
		return (0);
	}
	return (SYNERR);
}
