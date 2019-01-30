/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:30:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/01/29 16:08:09 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_eval.h"


int	tree_add_sep(t_parser *parser)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->type = parser->current->type;
	add_to_tree(&(parser->tree), node);
	return (0);
}

int	tree_add_and_or(t_parser *parser)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->type = parser->current->type;
	add_to_tree(&(parser->tree), node);
	return (0);
}

int	tree_add_pipeline(t_parser *parser)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->pipeline = parser->pipeline;
	node->type = PIPE;
	add_to_tree(&(parser->tree), node);
	parser->pipeline = NULL;
	return (0);	
}

void	add_to_tree(t_ast_node **head, t_ast_node *to_add)
{

	if (*head == NULL)
	{
		*head = to_add;
		return;
	}
	if (to_add->type == PIPE)
	{
		if ((*head)->right == NULL)
			(*head)->right = to_add;
		else
		{
			(*head)->right->right = to_add;
		}
	}
	else if (to_add->type == SEMI_COL)
	{
		to_add->left = *head;
		*head = to_add;
	}
	else if ((to_add->type == OR_IF) || (to_add->type == AND_IF))
	{
		if ((*head)->type == SEMI_COL)
		{
			to_add->left = (*head)->right;
			(*head)->right = to_add;
		}
		else
		{
			to_add->left = *head;
			*head = to_add;
		}
	}
}
