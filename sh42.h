/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell3.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 12:42:10 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/27 15:09:39 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# include <term.h>
# include <termios.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft/libft.h"

# define BUFF_SIZE 8192
# define COM 0
# define COM_ARG 1
# define REDIRECT 2
# define PIPE_EXP 3
# define EXPR 4
# define WORD 5
# define SPECIAL 6
# define BQUOTE 7
# define LEFT_RED 8
# define DLEFT_RED 9
# define RIGHT_RED 10
# define DRIGHT_RED 11
# define D_AND 12
# define D_OR 13
# define LOGIC 14
# define VAR 15
# define ALT_U_A 1096489755
# define ALT_D_A 1113266971
# define ALT_R_A 1130044187
# define ALT_L_A 1146821403
# define U_ARROW 4283163
# define D_ARROW 4348699
# define R_ARROW 4414235
# define L_ARROW 4479771
# define HOME 4741915
# define END 4610843
# define SPACE 32
# define DELETE 2117294875
# define BACKSPACE 127
# define RETURN 10
# define TAB 9
# define CTRL_D 4
# define ALT_C 42947
# define PROMPT "42sh> "

extern char			*g_cmd;
extern int			g_idx;

typedef struct		s_token
{
	struct s_token	*next;
	char			*data;
	char			type;
}					t_token;

typedef struct		s_fdlist
{
	t_list			*head;
	t_list			*cur;
}					t_fdlist;

typedef struct		s_node
{
	struct s_node	*left;
	struct s_node	*right;
	char			*data;
	char			type;
}					t_node;

typedef struct		s_mlist
{
	t_fdlist		*fdlist;
	t_list			*env;
}					t_mlist;

typedef struct winsize	t_winsize;

typedef struct		s_copy
{
	char			*copy;
	int				visual_mode;
	int				start;
}					t_copy;

typedef	struct		s_keys
{
	int				key;
	void			(*f)(t_dlist **, int visual, t_mlist *mlist);
}					t_keys;

typedef struct		s_builtin
{
	char			*cmd;
	int				(*f)(char **, t_mlist *);
}					t_builtin;

typedef enum		e_state
{
	L_MAIN = 0,
	L_SPEC,
	L_BQUOTEM,
	L_BQUOTED,
	L_DQUOTE,
	L_QUOTE
}					t_state;

/*
** main.c
*/
int					ft_compute(t_token **list, t_mlist *mlist);

/*
** ft_analyser.c
*/
char				*ft_analyser(char *cmd, t_mlist *mlist);

/*
** ft_lexer.c
*/
void				ft_lexer(char *str, t_token **list, int save_com);

/*
** ft_lexer_fun.c
*/
char				is_special(char *str);
void				ft_lexbquote(char **str, char *buf, int *i, t_token **list);
void				ft_lexdquote(char **str, char *buf, int *i, t_token **list);
void				ft_lexquote(char **str, char *buf, int *i, t_token **list);
void				ft_lexmain(char **str, char *buf, int *i, t_token **list);

/*
** ft_parser.c
*/
t_node				*ft_parser(t_token *list);

/*
** ft_parse_fun.c
*/
char				parse_pipe(t_token **list, t_node **tree);

/*
** ft_token.c
*/
int					ft_token_clear(t_token **list);
char				ft_tokenstep(t_token **list);
t_token				*ft_tokenpushback(t_token **token, char *data, char type);
t_token				*ft_token_split(char *s, char *special);

/*
** ft_node.c
*/
int					ft_clear_tree(t_node **tree);
t_node				*ft_nodenew(char type);
void				ft_nodeaddlast(t_node **tree, char left, t_node *node);

/*
** ft_checkpath.c
*/
char				*ft_checkpath(char *cmd, char **environ);

/*
** ft_envman.c
*/
t_list				*ft_duplicate(char **environ);
t_list				*ft_get_env(char *get, t_list *env);
char				**ft_tochar(t_list *env);

/*
** ft_signhandler.c
*/
void				ft_sighandler(int signal);
void				ft_sighand2(int signal);

/*
** ft_builtin.c
*/
int					ft_builtin(t_mlist *mlist, t_node *tree);

/*
** ft_is_builtin.c
*/
int					ft_is_builtin(char *cmd);

/*
** ft_cd.c
*/
int					ft_cd(char **cmd, t_mlist *mlist);

/*
** ft_cd_fun.c
*/
void				ft_cd_freejoin(t_list *tmp, const char *str, char *to_join);

/*
** ft_echo.c
*/
int					ft_echo(char **cmd, t_mlist *mlist);

/*
** ft_echo_utf.c
*/
void				ft_itoutf(int nb);

/*
** ft_notfnd.c
*/
void				ft_notfnd(char *cmd);

/*
** ft_pfd_manage.c
*/
void				ft_pfd_manage(int *pfd, int *pfd2);
void				ft_pfd_close(int *pfd);

/*
** ft_cmd_handler.c
*/
char				**ft_arg_handler(t_node *tree, char *cmd);
int					ft_cmd_handler(t_node *tree, t_mlist *mlist, int **tpfd);

/*
** ft_red_handler.c
*/
int					ft_red_handler(t_node *tree, t_mlist *mlist, int check);

/*
** ft_red_open.c
*/
void				ft_red_open(t_fdlist **fdlist, t_node *tree);

/*
** ft_token_handler.c
*/
int					ft_expr_handler(t_node *tree, t_mlist *mlist);

/*
** ft_get_bquote.c
*/
void				ft_get_bquote(t_token **list, t_mlist *mlist);

/*
** ft_utility_fun.c
*/
t_winsize			*ft_get_winsz(void);
int					*ft_reset_std(void);
t_copy				*ft_get_copy(void);
char				*ft_insertchar(char c, char *cmd, int idx);
void				ft_close_fdlist(t_fdlist **fdlist);

/*
** ft_term_fun.c
*/
int					ft_set_term(void);
int					ft_reset_term(void);

/*
** ft_read_keys.c
*/
char				*ft_read_keys(t_dlist *list, int noctrld, t_mlist *mlist);

/*
** ft_keys_fun.c
*/
void				ft_backspace(t_dlist **list, int visual, t_mlist *mlist);
void				ft_delete(t_dlist **list, int visual, t_mlist *mlist);
void				ft_home(t_dlist **list, int visual, t_mlist *mlist);
void				ft_end(t_dlist **list, int visual, t_mlist *mlist);
void				ft_ctrl_d(t_dlist **list, int visual, t_mlist *mlist);

/*
** ft_keys_fun2.c
*/
void				ft_u_arrow(t_dlist **list, int visual, t_mlist *mlist);
void				ft_d_arrow(t_dlist **list, int visual, t_mlist *mlist);
void				ft_l_arrow(t_dlist **list, int visual, t_mlist *mlist);
void				ft_r_arrow(t_dlist **list, int visual, t_mlist *mlist);

/*
** ft_keys_fun3.c
*/
void				ft_alt_u_arrow(t_dlist **list, int visual, t_mlist *mlist);
void				ft_alt_d_arrow(t_dlist **list, int visual, t_mlist *mlist);
void				ft_alt_l_arrow(t_dlist **list, int visual, t_mlist *mlist);
void				ft_alt_r_arrow(t_dlist **list, int visual, t_mlist *mlist);
void				ft_return(t_dlist **list, int visual, t_mlist *mlist);

/*
** ft_keys_fun4.c
*/
void				ft_tab(t_dlist **list, int visual, t_mlist *mlist);

/*
** ft_putchar_tc.c
*/
int					ft_putchar_tc(int c);

/*
** ft_log.c
*/
t_dlist				*ft_log_to_dlist(void);
void				ft_append_cmd_to_log(char *cmd);

/*
** ft_autocomp.c
*/
char				*ft_autocomp(char *fullpath, int exec, t_mlist *mlist);

/*
** ft_autocomp_fun.c
*/
char				*ft_complete(t_list *file_l, char *filename);

/*
** ft_select.c
*/
char				*ft_select(t_list *file_l, char *filename);

/*
** ft_slct_dep.c
*/
int					ft_slct_dep(t_list *file_l, int *pfd);

/*
** get_next_line.c
*/
int					get_next_line(int fd, char **line);

/*
** ft_error.c
*/
int					ft_error(char *filename, char *error);

#endif
