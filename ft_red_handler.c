/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 13:20:14 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/04 14:10:55 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static int		ft_drred_handler(t_node *tree)
{
	int			fd;

	fd = open(tree->data, O_WRONLY | O_APPEND |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
	dup2(fd, 1);
	return (1);
}

static int		ft_rred_handler(t_node *tree)
{
	int			fd;

	fd = open(tree->data, O_WRONLY | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
	dup2(fd, 1);
	return (1);
}

static int		ft_dlred_handler(t_node *tree)
{
	int			fd;
	int			ret;
	char		buf[BUFF_SIZE];

	fd = open(".dump", O_WRONLY |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | O_APPEND);
	while (42)
	{
		ft_putstr("> ");
		ret = read(0, buf, BUFF_SIZE);
		buf[ret] = '\0';
		if (ft_strnequ(buf, tree->data, ft_strlen(buf) - 1))
			break ;
		ft_putstr_fd(buf, fd);
	}
	close(fd);
	fd = open(".dump", O_RDONLY);
	dup2(fd, 0);
	ft_remove_file(".dump");
	return (1);
}

static int		ft_lred_handler(t_node *tree)
{
	int			fd;

	fd = open(tree->data, O_RDONLY);
	dup2(fd, 0);
	return (1);
}

int				ft_red_handler(t_node *tree)
{
	if (!tree)
		return (0);
	if (tree->type == LEFT_RED)
		ft_lred_handler(tree);
	if (tree->type == DLEFT_RED)
		ft_dlred_handler(tree);
	if (tree->type == RIGHT_RED)
		ft_rred_handler(tree);
	if (tree->type == DRIGHT_RED)
		ft_drred_handler(tree);
	return (ft_red_handler(tree->left));
}
