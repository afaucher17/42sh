/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 16:45:07 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/04 14:11:07 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

int				ft_red_open(t_node *tree)
{
	int			fd;

	if (!tree)
		return (0);
	if (tree->type == RIGHT_RED || tree->type == DRIGHT_RED)
	{
		fd = open(tree->data, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
		close(fd);
	}
	ft_red_open(tree->left);
	ft_red_open(tree->right);
	return (1);
}
