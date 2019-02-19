/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/19 19:33:51 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

// this should be one function

int	ft_wordexp(t_token *word, t_bool is_redir)
{
	if (handle_tilde(word) == MEMERR)
		return (MEMERR);
	if (handle_exp_param(word) == MEMERR)
		return (MEMERR);
	if ((is_redir == FT_FALSE) && (handle_field_split(word) == MEMERR)) 
		return (MEMERR);
	if (quote_removal(word) == MEMERR)
		return (MEMERR);
return (0);
}
