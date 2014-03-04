/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 13:06:24 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/04 19:02:04 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

char			**ft_arg_handler(t_node *tree, char *cmd)
{
	char		**com;
	t_node		*save;
	int			i;

	save = tree;
	i = 0;
	while ((save = save->right) != NULL)
		i++;
	com = (char**)malloc(sizeof(char*) * (i + 2));
	i = 1;
	com[0] = ft_strdup(cmd);
	free(cmd);
	while ((tree = tree->right) != NULL)
	{
		com[i] = ft_strdup(tree->data);
		i++;
	}
	com[i] = NULL;
	return (com);
}

static int		ft_pipe_handler(t_node *tree, t_list **env, int *pfd)
{
	int			pfd2[2];

	pipe(pfd2);
	if (tree->type == COM)
		return (ft_cmd_handler(tree, env, pfd, NULL));
	if (tree->left)
		ft_cmd_handler(tree->left, env, pfd, pfd2);
	if (tree->right)
		return (ft_pipe_handler(tree->right, env, pfd2));
	return (0);
}

static void		ft_logic_handler(t_node *tree, t_list **env, int ret, int op)
{
	int			ret2;
	t_node		*node;

	
	if (tree->type == COM || tree->type == PIPE_EXP)
		node = tree;
	else
		node = tree->left;
	if (op == D_OR)
		ret2 = ret || ft_pipe_handler(node, env, NULL);
	if (op == D_AND)
		ret2 = ret && ft_pipe_handler(node, env, NULL);
	if (tree->type != COM && tree->type != PIPE_EXP)
		ft_logic_handler(tree->right, env, ret2, tree->type);
}

int				ft_expr_handler(t_node *tree, t_list **env)
{
	if (!tree)
		return (0);
	if (tree->left)
	{
		ft_red_open(tree->left);
		ft_logic_handler(tree->left, env, 0, D_OR);
	}
	if (tree->right)
		ft_expr_handler(tree->right, env);
	return (1);
}
