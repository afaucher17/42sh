/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 13:20:14 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/05 17:13:38 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static int		ft_drred_handler(t_node *tree, t_list **list)
{
	int			fd;

	if ((fd = open(tree->data, O_WRONLY | O_APPEND |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP)) == -1)
		ft_error(tree->data, "Permission denied");
	ft_lstadd(list, ft_lstnew(&fd, sizeof(int)));
	dup2(fd, 1);
	return (1);
}

static int		ft_rred_handler(t_node *tree, t_list **list)
{
	int			fd;

	if ((fd = open(tree->data, O_WRONLY | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP)) == -1)
		ft_error(tree->data, "Permission denied");
	ft_lstadd(list, ft_lstnew(&fd, sizeof(int)));
	dup2(fd, 1);
	return (1);
}

static int		ft_dlred_handler(t_node *tree)
{
	int			fd;
	char		*buff;

	if ((fd = open(".dump", O_WRONLY |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | O_TRUNC)) == -1)
		ft_error(".dump", "Permission denied");
	while (42)
	{
		ft_putstr("heredoc> ");
		buff = ft_read_keys(ft_log_to_dlist());
		ft_bzero(g_cmd, BUFF_SIZE);
		g_idx = 0;
		if (ft_strnequ(buff, tree->data, ft_strlen(buff) - 1))
			break ;
		ft_putstr_fd(buff, fd);
		free(buff);
	}
	close(fd);
	if ((fd = open(".dump", O_RDONLY)) == -1)
		ft_error(".dump", "Permission denied");
	dup2(fd, 0);
	unlink("./.dump");
	return (1);
}

static int		ft_lred_handler(t_node *tree, t_list **list)
{
	int			fd;

	if ((fd = open(tree->data, O_RDONLY)) == -1)
		ft_error(tree->data, "No such file or directory");
	ft_lstadd(list, ft_lstnew(&fd, sizeof(int)));
	dup2(fd, 0);
	return (1);
}

int				ft_red_handler(t_node *tree, t_list **list)
{
	if (!tree)
		return (0);
	if (tree->type == LEFT_RED)
		ft_lred_handler(tree, list);
	if (tree->type == DLEFT_RED)
		ft_dlred_handler(tree);
	if (tree->type == RIGHT_RED)
		ft_rred_handler(tree, list);
	if (tree->type == DRIGHT_RED)
		ft_drred_handler(tree, list);
	return (ft_red_handler(tree->left, list));
}
