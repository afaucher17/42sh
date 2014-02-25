/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 14:18:26 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/04 15:48:01 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char			parse_expr(t_token **list, t_node **tree)
{
	t_node		*node;
	t_token		*save;

	if ((node = ft_nodenew(EXPR)) != NULL && parse_pipe(list, &node->left))
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

t_node		*ft_parser(t_token *list)
{
	t_node	*tree;

	tree = NULL;
	if (list == NULL)
		return (NULL);
	if (!parse_expr(&list, &tree))
	{
		ft_clear_tree(&tree);
		ft_putendl_fd("ft_sh3: parse error", 2);
		return (tree);
	}
	return (tree);
}
