/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 14:24:05 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 11:39:34 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static char		*proper_join(char *s1, char *s2)
{
	size_t		s1_len;
	size_t		s2_len;
	char		*result;

	s1_len = (s1) ? ft_strlen(s1) : 0;
	s2_len = ft_strlen(s2);
	result = ft_strnew(s1_len + s2_len);
	if (result)
	{
		if (s1)
			ft_memcpy(result, s1, s1_len);
		ft_memcpy(result + s1_len, s2, s2_len);
	}
	if (s1)
		ft_strdel(&s1);
	return (result);
}

static int		cut_at_newline(char **save_buff, char **line)
{
	char		*delimiter;

	if ((delimiter = ft_strchr(*save_buff, '\3')))	
	{
		*line = ft_strsub(*save_buff, 0, delimiter - *save_buff);
		ft_strcpy(*save_buff, delimiter + 1);
		return (1);
	}
	return (0);
}

static int		get_next_cmd(int const fd, char **line)
{
	int			bytes_read;
	char		buff[BUFF_SIZE + 1];
	static char	*save_buff = NULL;

	if (save_buff && cut_at_newline(&save_buff, line))
		return (1);
	while ((bytes_read = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[bytes_read] = '\0';
		save_buff = proper_join(save_buff, buff);
		if (cut_at_newline(&save_buff, line))
			return (1);
	}
	if (bytes_read < 0)
		return (-1);
	if (save_buff && *save_buff)
	{
		*line = ft_strdup(save_buff);
		ft_strdel(&save_buff);
		return (1);
	}
	if (save_buff)
		ft_strdel(&save_buff);
	return (0);
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
