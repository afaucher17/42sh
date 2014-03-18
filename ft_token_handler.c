/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 13:06:24 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 20:46:13 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static int		ft_pipe_handler(t_node *tree, t_mlist *mlist, int *pfd)
{
	int			pfd2[2];
	int			*tpfd[2];
	int			ret;

	pipe(pfd2);
	tpfd[0] = pfd;
	if (tree->type == COM)
		tpfd[1] = NULL;
	else
		tpfd[1] = pfd2;
	ft_red_open(&(mlist->fdlist), tree);
	if (tree->type == COM)
	{
		ret = ft_cmd_handler(tree, mlist, tpfd);
		ft_close_fdlist(&(mlist->fdlist));
		return (ret);
	}
	if (tree->left)
		ft_cmd_handler(tree->left, mlist, tpfd);
	ft_close_fdlist(&(mlist->fdlist));
	if (tree->right)
		return (ft_pipe_handler(tree->right, mlist, pfd2));
	return (0);
}

static void		ft_logic_handler(t_node *tree, t_mlist *mlist, int ret, int op)
{
	int			ret2;
	t_node		*node;

	if (tree->type == COM || tree->type == PIPE_EXP)
		node = tree;
	else
		node = tree->left;
	if (op == D_OR)
		ret2 = ret || ft_pipe_handler(node, mlist, NULL);
	if (op == D_AND)
		ret2 = ret && ft_pipe_handler(node, mlist, NULL);
	if (tree->type != COM && tree->type != PIPE_EXP)
		ft_logic_handler(tree->right, mlist, ret2, tree->type);
}

int				ft_expr_handler(t_node *tree, t_mlist *mlist)
{
	if (!tree)
		return (0);
	if (tree->left)
		ft_logic_handler(tree->left, mlist, 0, D_OR);
	if (tree->right)
		ft_expr_handler(tree->right, mlist);
	return (1);
}
