/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 15:02:29 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 15:43:56 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# define TERM_INIT "ti"
# define TERM_END "te"
# define UNDERLINE_S "us"
# define UNDERLINE_E "ue"
# define REV_VIDEO_S "mr"
# define REV_VIDEO_E "me"
# define HIDE_CURSOR "vi"
# define SHOW_CURSOR "ve"
# define DELETE_LINE "dl"
# define GO_TOP_LEFT "ho"
# define CLEAR_NEXT "cd"

# define UNDERLINE 1
# define REV_VIDEO 2

# define SLCT_KEY_DOWN 4348699
# define SLCT_KEY_UP 4283163
# define SLCT_KEY_LEFT 4479771
# define SLCT_KEY_RIGHT 4414235
# define SLCT_KEY_SPACE 32
# define SLCT_KEY_RETURN 10
# define SLCT_KEY_DELETE 2117294875
# define SLCT_KEY_BACKSPACE 127
# define SLCT_KEY_ESCAPE 27

# include <stdlib.h>
# include <termios.h>
typedef struct	s_lst
{
	char			*label;
	size_t			length;
	int				selected;
	struct s_lst	*next;
	struct s_lst	*prev;
}				t_lst;
typedef struct	s_select
{
	t_lst			*list;
	t_lst			*current;
	int				fd;
	size_t			margin;
	size_t			size;
	struct winsize	wsize;
}				t_select;
typedef struct	s_keys2
{
	int		key;
	void	(*key_run)(t_select *, int *);
}				t_keys2;
extern t_select	*slct;
/*
** TERM
*/
void	move_to(int x, int y);
void	load_term(void);
void	restore_term(void);
void	proper_exit(int ret);
size_t	get_margin(t_select *slct);
/*
** LISTS
*/
void	lst_pushback(t_lst **list, char *str);
t_lst	*fill_list(t_lst **list, int ac, char **av);
void	draw_list(t_select *slct);
void	lst_delelem(t_select *slct);
void	lst_free(t_lst **lst);
/*
** WRITE
*/
int		tputs_putc(int c);
void	put_flag(const char *flag);
void	putstr_flag(char *str, const int style);
void	put_error(const char *str);
/*
** SIGNALS
*/
void	load_signals(void);
/*
** KEYS
*/
void	key_dispatch(t_select *slct, int key, int *pfd);
void	slct_key_down(t_select *slct, int *pfd);
void	slct_key_escape(t_select *slct, int *pfd);
void	slct_key_left(t_select *slct, int *pfd);
void	slct_key_return(t_select *slct, int *pfd);
void	slct_key_right(t_select *slct, int *pfd);
void	slct_key_up(t_select *slct, int *pfd);
#endif /* !FT_SELECT_H */
