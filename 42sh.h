/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell3.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 12:42:10 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/06 19:39:36 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef				_42SH_H
# define			_42SH_H

# include			<term.h>
# include			<termios.h>
# include			<signal.h>
# include			<sys/types.h>
# include			<sys/ioctl.h>
# include			<stdlib.h>
# include			<fcntl.h>
# include			"libft/libft.h"
# define BUFF_SIZE	8192
# define COM		0
# define COM_ARG	1
# define REDIRECT	2
# define PIPE_EXP	3
# define EXPR		4
# define WORD		5
# define SPECIAL	6
# define BQUOTE		7
# define LEFT_RED	8
# define DLEFT_RED	9
# define RIGHT_RED	10
# define DRIGHT_RED	11
# define D_AND		12
# define D_OR		13
# define LOGIC		14
# define VAR		15
# define ALT_U_A	1096489755
# define ALT_D_A	1113266971
# define ALT_R_A	1130044187
# define ALT_L_A	1146821403
# define U_ARROW	4283163
# define D_ARROW	4348699
# define R_ARROW	4414235
# define L_ARROW	4479771
# define HOME		4741915
# define END		4610843
# define SPACE		32
# define DELETE		2117294875
# define BACKSPACE	127
# define RETURN		10
# define CTRL_D		4
# define ALT_C		42947
# define PROMPT		"42sh> "

extern char			*g_cmd;
extern int			g_idx;

typedef struct		s_token
{
	struct s_token	*next;
	char			*data;
	char			type;
}					t_token;

typedef struct		s_node
{
	struct s_node	*left;
	struct s_node	*right;
	char			*data;
	char			type;
}					t_node;

typedef struct		winsize t_winsize;

typedef struct		s_copy
{
	char			*copy;
	int				visual_mode;
	int				start;
}					t_copy;

typedef	struct		s_keys
{
	int				key;
	void			(*f)(t_dlist **, int visual);
}					t_keys;

enum				e_state
{
	L_MAIN = 0,
	L_SPEC,
	L_BQUOTEM,
	L_BQUOTED,
	L_DQUOTE,
	L_QUOTE
};

/*
** main.c
*/
int				ft_compute(t_token **list, t_list **env);

/*
** ft_analyser.c
*/
char			*ft_analyser(char *cmd);

/*
** ft_lexer.c
*/
void			ft_lexer(char *str, t_token **list, int save_com);

/*
** ft_lexer_fun.c
*/
char			is_special(char *str);
void			ft_lexbquote(char **str, char *buf, int *i, t_token **list);
void			ft_lexdquote(char **str, char *buf, int *i, t_token **list);
void			ft_lexquote(char **str, char *buf, int *i, t_token **list);
void			ft_lexmain(char **str, char *buf, int *i, t_token **list);

/*
** ft_parser.c
*/
t_node			*ft_parser(t_token *list);

/*
** ft_parse_fun.c
*/
char			parse_pipe(t_token **list, t_node **tree);

/*
** ft_token.c
*/
int				ft_token_clear(t_token **list);
char			ft_tokenstep(t_token **list);
t_token			*ft_tokenpushback(t_token **token, char *data, char type);
t_token			*ft_token_split(char *s, char *special);

/*
** ft_node.c
*/
int				ft_clear_tree(t_node **tree);
t_node			*ft_nodenew(char type);
void			ft_nodeaddlast(t_node **tree, char left, t_node *node);

/*
** ft_checkpath.c
*/
char			*ft_checkpath(char *split, char **environ);

/*
** ft_envman.c
*/
t_list			*ft_duplicate(char **environ);
char			**ft_tochar(t_list *env);

/*
** ft_signhandler.c
*/
void			ft_sighandler(int signal);
void			ft_sighand2(int signal);

/*
** ft_builtin.c
*/
int				ft_builtin(char **cmd, t_list **env);

/*
** ft_is_builtin.c
*/
int				ft_is_builtin(char *cmd);

/*
** ft_cdenv.c
*/
int				ft_cdenv(char **cmd, t_list **env);

/*
** ft_echo.c
*/
int				ft_echo(char **cmd);

/*
** ft_echo_utf.c
*/
void			ft_itoutf(int nb);

/*
** ft_notfnd.c
*/
void			ft_notfnd(char *cmd);

/*
** ft_chdir.c
*/
int				ft_chdir(char *cmd);

/*
** ft_cmd_handler.c
*/
int				ft_cmd_handler(t_node *tree, t_list **env, int *pfd,
									int *pfd2);

/*
** ft_red_handler.c
*/
int				ft_red_handler(t_node *tree, t_list **list);

/*
** ft_red_open.c
*/
int				ft_red_open(t_node *tree);

/*
** ft_token_handler.c
*/
char			**ft_arg_handler(t_node *tree, char *cmd);
int				ft_expr_handler(t_node *tree, t_list **env);

/*
** ft_get_bquote.c
*/
void			ft_get_bquote(t_token **list, t_list **env);

/*
** ft_utility_fun.c
*/
t_winsize		*ft_get_winsz(void);
int				*ft_reset_std(void);
t_copy			*ft_get_copy(void);
char			*ft_insertchar(char c, char *cmd, int idx);
void			ft_close_fdlist(t_list **list);

/*
** ft_term_fun.c
*/
int				ft_set_term(void);
int				ft_reset_term(void);

/*
** ft_read_keys.c
*/
char			*ft_read_keys(t_dlist *list);

/*
** ft_keys_fun.c
*/
void			ft_backspace(t_dlist **list, int visual);
void			ft_delete(t_dlist **list, int visual);
void			ft_home(t_dlist **list, int visual);
void			ft_end(t_dlist **list, int visual);
void			ft_ctrl_d(t_dlist **list, int visual);

/*
** ft_keys_fun2.c
*/
void			ft_u_arrow(t_dlist **list, int visual);
void			ft_d_arrow(t_dlist **list, int visual);
void			ft_l_arrow(t_dlist **list, int visual);
void			ft_r_arrow(t_dlist **list, int visual);

/*
** ft_keys_fun3.c
*/
void			ft_alt_u_arrow(t_dlist **list, int visual);
void			ft_alt_d_arrow(t_dlist **list, int visual);
void			ft_alt_l_arrow(t_dlist **list, int visual);
void			ft_alt_r_arrow(t_dlist **list, int visual);
void			ft_return(t_dlist **list, int visual);

/*
** ft_putchar_tc.c
*/
int				ft_putchar_tc(int c);

/*
** ft_log.c
*/
t_dlist			*ft_log_to_dlist(void);
void			ft_append_cmd_to_log(char *cmd);

/*
** ft_error.c
*/
void			ft_error(char *filename, char *error);

#endif				/* !_42SH_H */
