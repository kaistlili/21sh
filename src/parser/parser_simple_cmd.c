/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:44:14 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/25 21:52:54 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	expect_simple_cmd(t_parser *parser)
{
	t_token	*backtrack;
	int		ret;

	ft_bzero(&(parser->cmd), sizeof(t_simple_cmd));
	backtrack = parser->current;
	ret = 0;
	if (!(ret = expect_cmd_pre(parser)))
	{
		if (!(ret = expect_cmd_name(parser)))
			if (((ret = expect_cmd_suffix(parser)) != SYNERR)
					&& (ret))
				return (wrapper_free_cmd(ret, parser));
		return (0);
	}
	else if (!(ret = expect_cmd_name(parser)))
	{
		if (((ret = expect_cmd_suffix(parser)) != SYNERR) && (ret))
			return (wrapper_free_cmd(ret, parser));
		return (0);
	}
	free_simple_cmd(&(parser->cmd));
	parser->current = backtrack;
	return (ret);
}

int	expect_assign(t_parser *parser)
{
	int ret;

	if (parser_is_assign(parser->current))
	{
		parser->current->type = ASSIGN;
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_filename(t_parser *parser)
{
	int ret;

	if (parser->current->type == WORD)
	{
		parser->current->type = FILENAME;
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_word(t_parser *parser)
{
	int ret;

	if (parser->current->type == WORD)
	{
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_cmd_name(t_parser *parser)
{
	int	ret;

	ret = 0;
	if ((parser->current->type == WORD)
			&& (!parser_is_assign(parser->current)))
	{
		if (ret)
			return (ret);
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}
