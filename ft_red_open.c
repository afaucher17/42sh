/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 16:45:07 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/11 19:42:07 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static void		ft_fdlistpushback(t_fdlist **fdlist, int fd)
{
	t_list		*new;

	new = ft_lstnew(&fd, sizeof(int));
	if (!fdlist || !*fdlist)
	{
		if (!((*fdlist) = (t_fdlist*)malloc(sizeof(t_fdlist))))
			return ;
		(*fdlist)->head = new;
		(*fdlist)->cur = new;
	}
	else
	{
		ft_lstpushback(&((*fdlist)->head), &fd, sizeof(int));
		(*fdlist)->cur = (*fdlist)->head;
	}
}

void			ft_red_open(t_fdlist **fdlist, t_node *tree)
{
	int			fd;

	if (!tree)
		return ;
	if (tree->type == DRIGHT_RED)
		fd = open(tree->data, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP);
	if (tree->type == RIGHT_RED)
		fd = open(tree->data, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP);
	if (tree->type == LEFT_RED)
		fd = open(tree->data, O_RDONLY);
	if (tree->type == DRIGHT_RED || tree->type == RIGHT_RED || tree->type == LEFT_RED)
		ft_fdlistpushback(fdlist, fd);
	ft_red_open(fdlist, tree->left);
}
