/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 14:18:26 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/15 19:05:19 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int			is_logic(char *str, t_node *node)
{
	if (node->type == D_AND || node->type == D_OR)
		return (1);
	if (ft_strequ(str, "&&"))
	{
		node->type = D_AND;
		return (1);
	}
	if (ft_strequ(str, "||"))
	{
		node->type = D_OR;
		return (1);
	}
	return (0);
}

static char			parse_logic(t_token **list, t_node **tree)
{
	t_node			*node;
	t_token			*save;

	if ((node = ft_nodenew(LOGIC)) != NULL && parse_pipe(list, &node->left))
	{
		save = *list;
		if (ft_tokenstep(list) && is_logic((*list)->data, node)
			&& (*list)->type == SPECIAL)
		{
			if (!ft_tokenstep(list) || !parse_logic(list, &node->right))
				return (!ft_clear_tree(&node));
		}
		else
			*list = save;
		if (node->right)
			*tree = node;
		else
		{
			*tree = node->left;
			free(node->data);
			free(node);
		}
		return (1);
	}
	return (!ft_clear_tree(&node));
}

static char			parse_expr(t_token **list, t_node **tree)
{
	t_node			*node;
	t_token			*save;

	if ((node = ft_nodenew(EXPR)) != NULL && parse_logic(list, &node->left))
	{
		save = *list;
		if (ft_tokenstep(list) && ft_strcmp((*list)->data, ";") == 0
					&& (*list)->type == SPECIAL)
		{
			if (ft_tokenstep(list) && !parse_expr(list, &node->right))
			{
				*list = save;
				ft_clear_tree(&node);
				return (0);
			}
		}
		*tree = node;
		return (1);
	}
	ft_clear_tree(&node);
	return (0);
}

t_node				*ft_parser(t_token *list)
{
	t_node			*tree;

	tree = NULL;
	if (list == NULL)
		return (NULL);
	if (!parse_expr(&list, &tree))
	{
		ft_clear_tree(&tree);
		ft_putendl_fd("42sh: parse error", 2);
		return (tree);
	}
	return (tree);
}
