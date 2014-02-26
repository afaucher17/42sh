/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 14:24:05 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/26 19:28:55 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static int			split_buffer(char **buf, char **line)
{
	char			*save_line;
	char			*save_buf;

	save_line = *line;
	save_buf = *buf;
	if (ft_strchr(*buf, 3))
	{
		*line = ft_strjoin(*line
				, ft_strsub(*buf, 0, ft_strchr(*buf, 3) - *buf));
		*buf = ft_strdup(ft_strchr(*buf, 3) + 1);
		free(save_buf);
		return (1);
	}
	*line = ft_strjoin(*line, *buf);
	free(save_line);
	return (0);
}

static int			get_next_cmd(int const fd, char **line)
{
	static int		old_fd = 0;
	static char		*buf = NULL;
	int				len;

	*line = ft_strdup("");
	if (buf && old_fd == fd)
		if (split_buffer(&buf, line))
			return (1);
	old_fd = fd;
	buf = ft_strnew(BUFF_SIZE);
	while ((len = read(fd, buf, BUFF_SIZE)) != -1)
	{
		buf[len] = '\0';
		if (len == 0)
			return (0);
		if (split_buffer(&buf, line))
			return (1);
		if (len < BUFF_SIZE)
			return (1);
	}
	return (-1);
}

t_dlist			*ft_log_to_dlist(void)
{
	int			fd;
	char		*line;
	t_dlist		*dlist;

	if ((fd = open(".log", O_RDONLY | O_CREAT,
						S_IRUSR | S_IWUSR | S_IRGRP)) == -1)
	{
		ft_putendl_fd("42sh: error when accessing log.", 2);
		return (NULL);
	}
	dlist = NULL;
	while (get_next_cmd(fd, &line) > 0)
	{
		ft_dlstpushfront(&dlist, line, ft_strlen(line) + 1);
		free(line);
	}
	ft_dlstpushfront(&dlist, "", 1);
	close(fd);
	return (dlist);
}

void			ft_append_cmd_to_log(char *cmd)
{
	int			fd;
	int			i;
	char		*dup;

	dup = ft_strdup(cmd);
	i = ft_strlen(dup);
	if (i > 0)
		dup[i - 1] = '\0';
	if ((fd = open(".log", O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP)) == -1)
	{
		ft_putendl_fd("42sh: error when accessing log.", 2);
		return ;
	}
	write(fd, dup, ft_strlen(dup));
	write(fd, "\3", 1);
	free(dup);
	close(fd);
}
