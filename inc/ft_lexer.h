/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/04 20:48:02 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

#include "sh_core.h"

#define DQUOTE_ERR 10
#define SQUOTE_ERR 11
#define BAD_SUB	12
#define INCOMPLETE_SUB 13
#define ENDOFINPUT 14 


#define INPUTSZ 24
#define TABLESZ 128
/*
 * new lex jump table
 */

typedef int (*t_func)(t_lexer*);

int handle_dquote(t_lexer *lexer_state);
int handle_digit(t_lexer *lexer_state);
int handle_common(t_lexer *lexer_state);
int handle_ampersand(t_lexer *lexer_state);
int handle_squote(t_lexer *lexer_state);
int handle_semic(t_lexer *lexer_state);
int handle_less(t_lexer *lexer_state);
int handle_great(t_lexer *lexer_state);
int handle_column(t_lexer *lexer_state);

/*
Lexer jump table

typedef int (*t_func)(char**, t_token*);

int handle_dquote(char **input, t_token *token);
int handle_digit(char **input, t_token *token);
int handle_common(char **input, t_token *token);
int handle_ampersand(char **input, t_token *token);
int handle_squote(char **input, t_token *token);
int handle_semic(char **input, t_token *token);
int handle_less(char **input, t_token *token);
int handle_great(char **input, t_token *token);
int handle_column(char **input, t_token *token);
 */
/*
	intermediate cmd functions
*/
/*t_str functions*/
int	str_putnstr(char *str, t_str *data, size_t n);
int	str_putc(char **c, t_str *data);
int	ft_str_realloc(t_str *str_st, size_t newsz);


/*random util functions*/
int	ft_is_whitespace(char c);

void	add_token(t_token **head, t_token *to_add);
t_token	*dup_token(t_token *token);
t_token	*new_token(int type);


/* lexer */
t_token	*ft_tokenizer(char *line);
int		ft_tokenizer_2(char *line, t_token **head);
//int	next_token(char **line, t_token *token);
int	next_token(char *line, t_token **head);
/* for light parser*/
int	rev_lex(char *line, t_token **head);

#endif
