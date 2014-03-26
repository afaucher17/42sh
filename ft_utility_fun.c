/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 17:07:08 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/26 18:34:37 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include				"42sh.h"

t_winsize				*ft_get_winsz(void)
{
	static t_winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return (&ws);
}

int						*ft_reset_std(void)
{
	static int			std[2] = {0, 0};
	static int			is_off = 0;

	if (!is_off)
	{
		std[0] = dup(0);
		std[1] = dup(1);
		is_off = 1;
	}
	return (std);
}

t_copy					*ft_get_copy(void)
{
	static t_copy		*copy = NULL;

	if (copy == NULL)
	{
		if ((copy = (t_copy*)malloc(sizeof(t_copy))) == NULL)
			return (NULL);
		copy->copy = NULL;
		copy->visual_mode = 0;
		copy->start = 0;
	}
	return (copy);
}

char					*ft_insertchar(char c, char *cmd, int idx)
{
	char		*new;
	int			i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(cmd) + 2);
	while (i < idx)
	{
		new[i] = cmd[i];
		i++;
	}
	new[i] = c;
	i++;
	while (cmd[i])
	{
		new[i] = cmd[i];
		i++;
	}
	return (new);
}

void					ft_close_fdlist(t_fdlist **fdlist)
{
	t_list		*save;
	int			fd;

	save = NULL;
	if ((*fdlist) && (*fdlist)->head)
		save = (*fdlist)->head;
	while (save)
	{
		fd = *((int*)save->content);
		if (fd != -1)
			close(fd);
		save = save->next;
	}
	if ((*fdlist) && (*fdlist)->head)
		ft_list_clear(&(*fdlist)->head);
	free(*fdlist);
	*fdlist = NULL;
}
