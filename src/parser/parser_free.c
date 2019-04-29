/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:49:01 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/25 19:25:42 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

void	free_parser(t_parser *parser)
{
	free_token_lst(parser->cmd.word_lst);
	free_token_lst(parser->cmd.assign_lst);
	free_redir_lst(parser->cmd.redir_lst);
	free_token_lst(parser->head);
	free_pipeline(parser->pipeline);
}
