/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 14:31:16 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/15 19:03:32 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static char		parse_arg(t_token **list, t_node **tree)
{
	t_node		*node;

	if ((node = ft_nodenew(COM_ARG)) != NULL && (*list)->type == WORD)
	{
		node->data = ft_strdup((*list)->data);
		ft_nodeaddlast(tree, 0, node);
		return (1);
	}
	ft_clear_tree(&node);
	return (0);
}

static char		parse_redirect(t_token **list, t_node **tree)
{
	t_node		*node;
	t_token		*save;

	save = *list;
	if ((node = ft_nodenew(REDIRECT)) != NULL
			&& (*list)->type == SPECIAL && ft_strchr("><", (*list)->data[0]))
	{
		node->type = ft_strequ((*list)->data, ">") ? RIGHT_RED : 0;
		node->type = ft_strequ((*list)->data, ">>") ? DRIGHT_RED : node->type;
		node->type = ft_strequ((*list)->data, "<") ? LEFT_RED : node->type;
		node->type = ft_strequ((*list)->data, "<<") ? DLEFT_RED : node->type;
		if (ft_tokenstep(list) && (*list)->type == WORD)
		{
			node->data = ft_strdup((*list)->data);
			save = *list;
			if (!ft_tokenstep(list) || !parse_redirect(list, &node->left))
				*list = save;
			ft_nodeaddlast(tree, 1, node);
			return (1);
		}
	}
	ft_clear_tree(&node);
	*list = save;
	return (0);
}

static char		parse_com(t_token **list, t_node **tree)
{
	t_node		*node;
	t_token		*save;
	int			red;
	int			com;

	save = *list;
	if ((node = ft_nodenew(COM)) == NULL)
		return (0);
	if ((red = (parse_redirect(list, &node->left))))
		save = *list;
	if ((com = ((!red || ft_tokenstep(list)) && (*list)->type == WORD)))
	{
		node->data = ft_strdup((*list)->data);
		save = *list;
		while (ft_tokenstep(list) && (parse_redirect(list, &node->left)
					|| parse_arg(list, &node->right)))
			save = *list;
	}
	if ((red || com) && (*list = save) && (*tree = node))
		return (1);
	ft_clear_tree(&node);
	*list = save;
	return (0);
}

char			parse_pipe(t_token **list, t_node **tree)
{
	t_node		*node;
	t_token		*save;

	if ((node = ft_nodenew(PIPE_EXP)) != NULL && parse_com(list, &node->left))
	{
		save = *list;
		if (ft_tokenstep(list) && ft_strequ((*list)->data, "|")
				&& (*list)->type == SPECIAL)
		{
			if (!ft_tokenstep(list) || !parse_pipe(list, &node->right))
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
