#include "../../ft_lexer.h"

void	add_token(t_token **head, t_token *to_add)
{
	t_token *tmp;

	tmp = *head;
	if (*head == NULL)
		*head = to_add;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = to_add;	
	}
}

t_token	*new_token(int	type)
{
	t_token *new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	if (!(new->data.str = ft_memalloc(INPUTSZ * sizeof(char))))
		return (NULL);
	new->data.size = INPUTSZ;
	new->type = type;
	return (new);	
}

void	free_token_lst(t_token *token)
{
	t_token *save;

	save = token;
	while (token)
	{
		save = token->next;
		free_token(token);
		token = save;
	}
}

void	free_token(t_token *token)
{
	if (token->data.str)
		free(token->data.str);
	free(token);
}

t_token	*dup_token(t_token *token)
{
	t_token *new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	ft_memcpy(new, token, sizeof(t_token));
	if (!(new->data.str = ft_strdup(token->data.str)))
		return (NULL);
	new->next = NULL;
	return (new);
}

int	str_putnstr(char *str, t_str *data, size_t n)
{
	char *ptr;

	ptr = str;

	while ((*str) && (n))
	{
		n--;
		if (str_putchar(&str, data) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	str_putchar(char **c, t_str *data)
{
	size_t i;

	i = data->len;
	data->str[i] = **c;
	*c = *c + 1;
	data->len = i + 1;
	if (data->len == data->size)
		if (ft_str_realloc(data, INPUTSZ) == MEMERR)
			return (MEMERR);
	return (0);	
}
/*
int	str_putchar(char c, t_str *data)
{
	size_t i;

	i = data->len;
	data->str[i] = c;
	data->len = i + 1;
	if (data->len == data->size)
		if (ft_str_realloc(data, INPUTSZ) == MEMERR)
			return (MEMERR);
	return (0);	
}
*/
/*
this has to be change to is_whitespace
*/
int	ft_is_whitespace(char c)
{
	static char *ifs = "\n\t ";

	int			i;

	i = 0;
	while (ifs[i])
	{
		if (ifs[i] == c)
			return (1);
		i++;
	}
	return (0);
}