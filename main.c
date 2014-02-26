/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 11:15:15 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/26 19:14:42 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static int		ft_compute(t_token **list, t_list **env)
{
	t_node		*tree;

	tree = ft_parser(*list);
	ft_expr_handler(tree, env);
	ft_token_clear(list);
	ft_clear_tree(&tree);
	return (1);
}

static char		*ft_init(char *buff)
{
	signal(SIGINT, ft_sighandler);
	ft_putstr(PROMPT);
	ft_set_term();
	buff = ft_read_keys(ft_log_to_dlist());
	ft_bzero(g_cmd, BUFF_SIZE);
	g_idx = 0;
	return (buff);
}

int				main(int ac, char **av, char **environ)
{
	char		*buff;
	t_token		*list;
	t_list		*env;
	
	(void)ac;
	(void)av;
	list = NULL;
	env = ft_duplicate(environ);
	if (!env)
		ft_lstpushback(&env, "PATH=", 5);
	while (42)
	{
		buff = ft_init(buff);
		ft_lexer(ft_analyser(buff), &list);
		free(buff);
		if (list)
			ft_compute(&list, &env);
	}
	return (0);
}
