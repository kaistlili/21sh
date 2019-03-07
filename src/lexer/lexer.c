/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/07 22:09:23 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"


t_lx_fn	g_lx_fn[] =\
{
	{'\n', &handle_newline},
	{'0', &handle_digit},
	{'1', &handle_digit},
	{'2', &handle_digit},
	{'3', &handle_digit},
	{'4', &handle_digit},
	{'5', &handle_digit},
	{'6', &handle_digit},
	{'7', &handle_digit},
	{'8', &handle_digit},
	{'9', &handle_digit},
	{'"', &handle_dquote},
	{'&', &handle_ampersand},
	{'\'', &handle_squote},
	{';', &handle_semic},
	{'<', &handle_less},
	{'>', &handle_great},
	{'|', &handle_column},
	{ 0, NULL},
};

int	dispatch_fn(t_lexer *lx_st)
{
	int i;

	i = 0;
	while (g_lx_fn[i].f)
	{
		if (g_lx_fn[i].c == *(lx_st->cursor))
			return (g_lx_fn[i].f(lx_st));
		i++;
	}
	return (handle_common(lx_st));
}

t_token *next_tok(char *line)
{
	static t_lexer lexer_state;
	static int		init = 1;

	if (init)
	{
		init = 0;
		ft_bzero(&lexer_state, sizeof(t_lexer));
	}
	if ((line))
	{
		lexer_state.line = line;
		lexer_state.cursor = line;
	}
	while (ft_cisin(" \t", *(lexer_state.cursor)))	
		lexer_state.cursor = lexer_state.cursor + 1;
	if (*(lexer_state.cursor) == '\0')
	{
		init = 1;
		return (new_token(EOI));
	}
	if (!(lexer_state.token = new_token(0))
		|| (dispatch_fn(&lexer_state) == MEMERR))
		return (NULL);
	return (lexer_state.token);
}

t_token *ft_tokenizer(char *line)
{
	t_lexer lexer_state;
	t_token	*head;

	head = NULL;
	lexer_state.line = line;
	lexer_state.cursor = line;
	while (ft_cisin(" \t", *(lexer_state.cursor)))	
		lexer_state.cursor = lexer_state.cursor + 1;
	while (*(lexer_state.cursor))
	{
		if (!(lexer_state.token = new_token(0)))
			return (NULL);
		if (dispatch_fn(&lexer_state) == MEMERR)
			return (NULL);
		add_token(&head, lexer_state.token);
		lexer_state.token = NULL;
		while (ft_cisin(" \t", *(lexer_state.cursor)))	
			lexer_state.cursor = lexer_state.cursor + 1;
	}
	add_token(&head, new_token(EOI));
	return (head);
}


int test_lexer(char *line)
{
	t_token *ret;

	while (42)
	{
		if (!(ret = next_tok (line)))
			return (MEMERR);
		print_token(ret);
		if (ret->type == EOI)
			break;
	}
	return (0);
}
