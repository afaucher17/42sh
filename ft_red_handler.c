/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 13:20:14 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 20:35:26 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static int		ft_drred_handler(t_node *tree, t_fdlist *fdlist)
{
	int			fd;

	if (!fdlist || !fdlist->cur)
		return (0);
	fd = *((int*)fdlist->cur->content);
	if (fd == -1)
		return (ft_error(tree->data, "Permission denied"));
	fdlist->cur = fdlist->cur->next;
	dup2(fd, 1);
	return (1);
}

static int		ft_rred_handler(t_node *tree, t_fdlist *fdlist)
{
	int			fd;

	if (!fdlist || !fdlist->cur)
		return (0);
	fd = *((int*)fdlist->cur->content);
	if (fd == -1)
		return (ft_error(tree->data, "Permission denied"));
	dup2(fd, 1);
	return (1);
}

static int		ft_dlred_handler(t_node *tree, t_mlist *mlist)
{
	int			fd;
	char		*buff;

	if ((fd = open(".dump", O_WRONLY |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | O_TRUNC)) == -1)
		return (ft_error(".dump", "Permission denied"));
	while (42)
	{
		ft_putstr("heredoc> ");
		ft_set_term();
		buff = ft_read_keys(ft_log_to_dlist(), 1, mlist);
		ft_reset_term();
		ft_bzero(g_cmd, BUFF_SIZE);
		g_idx = 0;
		if (ft_strnequ(buff, tree->data, ft_strlen(buff) - 1))
			break ;
		ft_putstr_fd(buff, fd);
		free(buff);
	}
	close(fd);
	if ((fd = open(".dump", O_RDONLY)) == -1)
		return (ft_error(".dump", "Permission denied"));
	dup2(fd, 0);
	unlink("./.dump");
	return (1);
}

static int		ft_lred_handler(t_node *tree, t_fdlist *fdlist)
{
	int			fd;

	if (!fdlist || !fdlist->cur)
		return (0);
	fd = *((int*)fdlist->cur->content);
	if ((fd = open(tree->data, O_RDONLY)) == -1)
		return (ft_error(tree->data, "No such file or directory"));
	dup2(fd, 0);
	return (1);
}

int				ft_red_handler(t_node *tree, t_mlist *mlist, int check)
{
	int			ret;
	t_fdlist	*fdlist;

	fdlist = mlist->fdlist;
	ret = 0;
	if (!tree)
		return (check);
	if (tree->type == LEFT_RED && check)
		ret = ft_lred_handler(tree, fdlist);
	if (tree->type == DLEFT_RED && check)
		ret = ft_dlred_handler(tree, mlist);
	if (tree->type == RIGHT_RED && check)
		ret = ft_rred_handler(tree, fdlist);
	if (tree->type == DRIGHT_RED && check)
		ret = ft_drred_handler(tree, fdlist);
	if (fdlist && fdlist->cur)
		fdlist->cur = fdlist->cur->next;
	return (ft_red_handler(tree->left, mlist, ret));
}
