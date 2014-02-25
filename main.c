/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 11:15:15 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/25 17:12:12 by tdieumeg         ###   ########.fr       */
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

static t_dlist	*fill_stack(t_dlist *stack, char *buff)
{
	int			i;
	char		*dup;

	dup = ft_strdup(buff);
	i = ft_strlen(dup);
	if (i > 0)
		dup[i - 1] = '\0';
	if (stack)
	{
		free(stack->content);
		stack->content = dup;
		stack->content_size = i + 1;
	}
	return (stack);
}

static char		*ft_init(t_dlist **stack, char *buff)
{
	signal(SIGINT, ft_sighandler);
	ft_putstr(PROMPT);
	ft_set_term();
	buff = ft_read_keys(*stack);
	ft_bzero(g_cmd, BUFF_SIZE);
	g_idx = 0;
	*stack = fill_stack(*stack, buff);
	return (buff);
}

int				main(int ac, char **av, char **environ)
{
	char		*buff;
	t_token		*list;
	t_list		*env;
	t_dlist		*stack;
	int			inhib[3] = {0, 0, 0};

	(void)ac;
	(void)av;
	stack = NULL;
	list = NULL;
	env = ft_duplicate(environ);
	if (!env)
		ft_lstpushback(&env, "PATH=", 5);
	ft_dlstpushfront(&stack, "", 1);
	while (42)
	{
		buff = ft_init(&stack, buff);
		ft_dlstpushfront(&stack, "", 1);
		ft_lexer(buff, stack, inhib, &list);
		free(buff);
		if (list)
			ft_compute(&list, &env);
	}
	return (0);
}
