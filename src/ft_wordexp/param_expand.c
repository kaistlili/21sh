/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 20:21:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_wordexp.h"

char *quote_str(char *str)
{
	size_t 	count;
	int		j;
	int		i;
	char	*quoted;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\'))
			count++;
		i++;
	}
	if (!(quoted = ft_strnew(i + count)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\'))
		{
			quoted[j] = '\\';
			j++;
		}
		quoted[j] = str[i];
		i++;
		j++;
	}
	return (quoted);
}

int	expand_param(t_str *str_w, int *index, char *to_insert)
{
	int		trunc;
	int		i;

	i = *index + 1;
	trunc = 1; /* single $*/
	if (str_w->str[i] == '{')
	{
		i++;
		trunc = 3;
	}
	while (parser_is_name_c(str_w->str[i]))
	{
		trunc++;
		i++;
	}
	ft_memmove(str_w->str + *index, str_w->str + *index + trunc, str_w->len - *index - trunc);
	str_w->len = str_w->len - trunc;
	str_w->str[str_w->len] = '\0';
	if (insert_str(str_w, index, to_insert) == MEMERR)
		return (MEMERR);
	return (0);
}

char *build_param(t_str *str_w, int index)
{
	char *value;
	static char *empty_str = "";

	if (str_w->str[index] == '{')
		index++;
	value = get_env_value(str_w->str + index);
	if (!value)
		value = empty_str;
	if (!(value = quote_str(value)))
		return (NULL); /*MEMERR*/
	return (value);
}


int	handle_exp_param(t_token *word)
{
	int index;
	char *value;
	int inside_dquote;

	index = 0;
	inside_dquote = 1; /* > 0 when outside dquotes, < 0 when inside dquotes */
	while (word->data.str[index])
	{
		if (word->data.str[index] == '"')
			inside_dquote = -inside_dquote; 
		if ((word->data.str[index] == '$') && (word->data.str[index + 1] != 0))
		{
			value = build_param(&(word->data), index + 1);
			if (!value)
				return (MEMERR);
			if (expand_param(&(word->data), &index, value) == MEMERR)
				return (MEMERR);
			continue;
		}
		else if ((word->data.str[index] == '\'') && (inside_dquote == 1))
			index = next_squote(word->data.str, index);
		else if (word->data.str[index] == '\\')
			index = next_bslash(word->data.str, index);
		index++;
	}
	return (0);
}
