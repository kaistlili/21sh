/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:50:56 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/22 16:27:19 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H
# include "libft.h"
# include <curses.h>
# include <termios.h>
# include <term.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include "ft_eval.h"

# define HT_SIZE 2048

# define K_SUP  "\33[1;2A"
# define K_SDOW "\33[1;2B"
# define K_SRGT "\33[1;2C"
# define K_SLFT "\33[1;2D"
# define K_DEL	"\33[3~"
# define K_UP	"\33[A"
# define K_LEFT	"\33[D"
# define K_RGHT	"\33[C"
# define K_DOWN	"\33[B"
# define K_END  "\33[F"
# define K_HOME "\33[H"
# define K_TAB	"\t"
# define K_CTRA	"\1"
# define K_CTRC	"\3"
# define K_CTRD	"\4"
# define K_ENTR	"\12"
# define K_CTRR	"\22"
# define K_CTRP	"\20"
# define K_CTRV	"\26"
# define K_CTRY	"\31"
# define K_ESC	"\33"
# define K_SPC	" "
# define K_BSPC "\177"

typedef struct		s_rdl
{
	struct termios	save;
	char			*prompt;
	int				curs;
	int				col;
	int				lpro;

	char			*str;
	int				size;
	int				allo;

	int				vcurs;
	char			*paste;
}					t_rdl;

typedef struct		s_hash
{
	char			*exec;
	char			*path;
}					t_hash;

typedef struct		s_key
{
	char			*key;
	int				(*f)(t_rdl *rdl, char *key);
}					t_key;

//main
char				*readline(char	*PROMPT);

//hashtable
void	ht_init(void);
int		ht_hash(char *path);
t_list	*ht_get(char *path);
t_list	*ht_getexec(char *path);
int 	ht_getvalue(char *path, t_cmd_tab *cmd);
void	ht_refreshall(char *path);

//termcaps
int		terminit(struct termios *save);
int		getcolumn(void);
int		termreset(struct termios *save);
void	tgpstr(char *s);

//keys
int		special_key(t_rdl *rdl, char *buf, t_key *key);
int	    key_router(t_rdl *rdl, char *buf);
int		next_word(t_rdl *rdl, char *buf);
int		prev_word(t_rdl *rdl, char *buf);
int		del_cara(t_rdl *rdl, char *buf);
int		begin(t_rdl *rdl, char *buf);
int		move_curs(t_rdl *rdl, char *buf);
int		enter(t_rdl *rdl, char *buf);
int		ctrld(t_rdl *rdl, char *buf);
int		ctrlc(t_rdl *rdl, char *buf);
int		autocompl(t_rdl *rdl, char *buf);
int		visualmode(t_rdl *rdl, char *buf);
int		vm_move(t_rdl *rdl, char *buf);
int		vm_copy(t_rdl *rdl, char *buf);
int		vm_del(t_rdl *rdl, char *buf);
int		paste(t_rdl *rdl, char *buf);
int		finish(t_rdl *rdl, char *buf);
int		end(t_rdl *rdl, char *buf);
int		history(t_rdl *rdl, char *buf);
int		ctrlr(t_rdl *rdl, char *buf);
int		normal_key(t_rdl *rdl, char *buf);
int		ctrlr(t_rdl *rdl, char *buf);
int		return2(t_rdl *rdl, char *buf);
t_list	*get_cplenv(char *match);

//tools
void	reprint(t_rdl *rdl, int curs);
int		is_special(char *buf);
int		left(t_rdl *rdl, int i);
int		right(t_rdl *rdl, int i);
int		vleft(t_rdl *rdl, int i);
int		vright(t_rdl *rdl, int i);
int		up(t_rdl *rdl, int i);
int		down(t_rdl *rdl, int i);

//file
t_list	*get_exec(char *exec, char *path);
t_list	*get_folex(char *token, int (*f)(char *file));
int		folexaccess(char *file);
int		exaccess(char *file);
int		filexist(char *file);

//struct rdl
int		rdlinit(t_rdl *rdl, char *PROMPT);
void	rdladd(t_rdl *rdl, char c);
void	rdldel(t_rdl *rdl, int curs);
void	rdladdstr(t_rdl *rdl, char *str);
void	rdlreplace(t_rdl *rdl, char *s);

//signal
void	setsig(void);

//print
void	putlst(char *mtc, t_list *lst, t_rdl *rdl);

//history
void	hstadd(char *str);
char	*hstnext(char *s);
char	*hstprev(void);
void	hstreset(void);
char	*hstchc(char *s);
void	hstaddfile(char **env);
int		hstread(char **env);
int 	hstnchc(t_rdl *rdl, char *buf);
int		hstdelcara(t_rdl *rdl, char	*buf);

#endif
