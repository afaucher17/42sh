/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 17:03:16 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/04 15:45:26 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"42sh.h"

int			ft_clear_tree(t_node **tree)
{
	if (!(*tree))
		return (0);
	if ((*tree)->left)
		ft_clear_tree(&((*tree)->left));
	if ((*tree)->right)
		ft_clear_tree(&((*tree)->right));
	free((*tree)->data);
	free(*tree);
	*tree = NULL;
	return (1);
}

t_node		*ft_nodenew(char type)
{
	t_node	*new;

	if ((new = (t_node*)malloc(sizeof(t_node))) == NULL)
			return (NULL);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	new->data = NULL;
	return (new);
}

void		ft_nodeaddlast(t_node **tree, char left, t_node *node)
{
	t_node	*cur;

	cur = *tree;
	if (!cur)
		*tree = node;
	else
	{
		if (left)
		{
			while (cur->left)
				cur = cur->left;
			cur->left = node;
		}
		else
		{
			while (cur->right)
				cur = cur->right;
			cur->right = node;
		}
	}
}
