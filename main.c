/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 11:15:15 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/24 17:39:18 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

int				ft_compute(t_token **list, t_mlist *mlist)
{
	t_node		*tree;

	tree = ft_parser(*list);
	ft_expr_handler(tree, mlist);
	ft_token_clear(list);
	ft_clear_tree(&tree);
	return (1);
}

static char		*ft_init(char *buff, t_mlist *mlist)
{
	signal(SIGINT, ft_sighandler);
	ft_putstr(PROMPT);
	ft_set_term();
	buff = ft_read_keys(ft_log_to_dlist(), 0, mlist);
	ft_reset_term();
	ft_bzero(g_cmd, BUFF_SIZE);
	g_idx = 0;
	return (buff);
}

void			ft_checktty(t_mlist *mlist)
{
	char		buff[BUFF_SIZE];
	char		*join;
	char		*tmp;
	t_token		*list;
	int			len;

	list = NULL;
	join = NULL;
	ft_bzero(buff, BUFF_SIZE);
	if (!isatty(0))
	{
		while ((len = read(0, buff, BUFF_SIZE - 1)) > 0)
		{
			buff[len] = '\0';
			tmp = join;
			join = ft_strjoin(tmp, buff);
			free(tmp);
		}
		ft_lexer(join, &list, 0);
		free(join);
		ft_get_bquote(&list, mlist);
		if (list)
			ft_compute(&list, mlist);
		exit(EXIT_SUCCESS);
	}
}

int				main(int ac, char **av, char **environ)
{
	char		*buff;
	t_token		*list;
	t_mlist		*mlist;

	(void)ac;
	(void)av;
	buff = NULL;
	list = NULL;
	mlist = (t_mlist*)malloc(sizeof(mlist));
	mlist->env = ft_duplicate(environ);
	ft_reset_std();
	if (!mlist->env)
		exit(!ft_putendl_fd("42sh: Restore environment before execution.", 2));
	ft_checktty(mlist);
	while (42)
	{
		buff = ft_init(buff, mlist);
		ft_lexer(ft_analyser(buff, mlist), &list, 1);
		free(buff);
		ft_get_bquote(&list, mlist);
		if (list)
			ft_compute(&list, mlist);
	}
	return (0);
}
