#include "ft_parser.h"
#include "readline.h"

static int here_doc_delimiter(t_token *io_here)
{
	size_t len;

	len = ft_strlen(io_here->data.str);
	if (quote_removal(io_here) == MEMERR)
		return (MEMERR);
	io_here->type = HERE_END;
	if (len > ft_strlen(io_here->data.str))
		io_here->type = HERE_END_QU;
	return (0);
}

static void	replace_here_doc(t_token *io_here, char *here_doc)
{
	free(io_here->data.str);
	io_here->data.str = here_doc;
	io_here->data.len = ft_strlen(here_doc);
	io_here->data.size = ft_strlen(here_doc) + 1;
}

static int interactive_heredoc(t_token *io_here)
{
	size_t len;
	char *here_doc;
	char *new_ln;

	len = ft_strlen(io_here->data.str);
	if (!(here_doc = ft_strdup("")))
		return (MEMERR);	
	while (42)
	{
		if (!(new_ln = readline("> ")))
			return (MEMERR);
		else if (*new_ln == '\0')
			return (HEREDOC_ERR);
		if ((!ft_strncmp(new_ln, io_here->data.str, len))
			&& (new_ln[len] == '\n'))
			break;
		if (!(here_doc = ft_strjoin(here_doc, new_ln)))
			return (MEMERR);
		free(new_ln);
	}
	free(new_ln);
	replace_here_doc(io_here, here_doc);
	return (0);
}

char *get_file_delim(char *next_nl, char *here_end)
{
	char *delim;
	int	len;

	if (!(delim = ft_strstr(next_nl, here_end)))
		return (NULL);
	len = ft_strlen(here_end);
	if ((delim[len] != '\n') && (delim[len] != '\0'))
		return (NULL);
	return (delim);
}

int handle_here_doc(t_parser *parser)
{
	char *next_nl;
	char *here_end;
	char *delim;
	char *here_doc;
	int len;

	if (here_doc_delimiter(parser->current) == MEMERR)
		return (MEMERR);
	if (g_sh.mode == INTERACTIVE)
		return (interactive_heredoc(parser->current));			
	if (!(here_end = ft_zprintf("\n%s", parser->current->data.str)))
		return (MEMERR);
	len = ft_strlen(here_end);
	if ((!(next_nl = ft_strchr(parser->cursor, '\n')))
		|| (!(delim = get_file_delim(next_nl, here_end))))
		return (HEREDOC_ERR);
	next_nl++;
	if (!(here_doc = ft_strndup(next_nl, delim - next_nl + 1)))
		return (MEMERR);
	len = delim - next_nl + ft_strlen(here_end) + 1;
	ft_memmove(next_nl, next_nl + len, ft_strlen(delim) + ft_strlen(here_end) + 1);	
	replace_here_doc(parser->current, here_doc);
	return (0);
}
