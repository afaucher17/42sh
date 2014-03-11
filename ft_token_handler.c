/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 13:06:24 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/11 16:08:46 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static int		ft_pipe_handler(t_node *tree, t_list **env, int *pfd,
								t_fdlist *fdlist)
{
	int			pfd2[2];
	int			*tpfd[2];

	pipe(pfd2);
	tpfd[0] = pfd;
	if (tree->type == COM)
		tpfd[1] = NULL;
	else
		tpfd[1] = pfd2;
	if (tree->type == COM)
		return (ft_cmd_handler(tree, env, tpfd, fdlist));
	if (tree->left)
		ft_cmd_handler(tree->left, env, tpfd, fdlist);
	if (tree->right)
		return (ft_pipe_handler(tree->right, env, pfd2, fdlist));
	return (0);
}

static void		ft_logic_handler(t_node *tree, t_list **env, int ret, int op)
{
	int			ret2;
	t_node		*node;
	t_fdlist	*fdlist;

	fdlist = NULL;
	if (tree->type == COM || tree->type == PIPE_EXP)
		node = tree;
	else
		node = tree->left;
	ft_red_open(&fdlist, node);
	if (op == D_OR)
		ret2 = ret || ft_pipe_handler(node, env, NULL, fdlist);
	if (op == D_AND)
		ret2 = ret && ft_pipe_handler(node, env, NULL, fdlist);
	ft_close_fdlist(&fdlist);
	if (tree->type != COM && tree->type != PIPE_EXP)
		ft_logic_handler(tree->right, env, ret2, tree->type);
}

int				ft_expr_handler(t_node *tree, t_list **env)
{
	if (!tree)
		return (0);
	if (tree->left)
		ft_logic_handler(tree->left, env, 0, D_OR);
	if (tree->right)
		ft_expr_handler(tree->right, env);
	return (1);
}
