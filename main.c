/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 11:15:15 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/08 21:32:58 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

int				ft_compute(t_token **list, t_list **env)
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
	ft_reset_term();
	ft_bzero(g_cmd, BUFF_SIZE);
	g_idx = 0;
	return (buff);
}

void			ft_checktty(t_list **env)
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
		ft_get_bquote(&list, env);
		if (list)
			ft_compute(&list, env);
		exit(EXIT_SUCCESS);
	}
}

int				main(int ac, char **av, char **environ)
{
	char		*buff;
	t_token		*list;
	t_list		*env;
	
	(void)ac;
	(void)av;
	buff = NULL;
	list = NULL;
	env = ft_duplicate(environ);
	ft_reset_std();
	if (!env)
		exit(!ft_putendl_fd("42sh: Restore environment before execution.", 2));
	ft_checktty(&env);
	while (42)
	{
		buff = ft_init(buff);
		ft_lexer(ft_analyser(buff), &list, 1);
		free(buff);
		ft_get_bquote(&list, &env);
		if (list)
			ft_compute(&list, &env);
	}
	return (0);
}
