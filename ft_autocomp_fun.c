/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomp_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 15:00:51 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 11:56:08 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static void			ft_delcur(t_list **cur, int i, char *filename)
{
	t_list			*prev;
	t_list			*tmp;
	t_list			*save;

	prev = NULL;
	tmp = *cur;
	while (tmp)
	{
		if (!ft_strnequ(filename, tmp->content, i + 1))
		{
			save = tmp;
			if (!prev)
				*cur = tmp->next;
			else
				prev->next = tmp->next;
			tmp = tmp->next;
			free(save->content);
			free(save);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

static int			ft_get_max_len(t_list *file_l)
{
	unsigned int	max;

	max = 0;
	while (file_l)
	{
		max = (max < file_l->content_size) ? file_l->content_size : max;
		file_l = file_l->next;
	}
	return (max);
}

static char			*ft_chk_list(t_list *file_l, char *filename)
{
	unsigned int	i;
	unsigned int	j;
	t_list			*save;
	char			*buf;
	char			c;

	i = ft_strlen(filename);
	j = 0;
	save = file_l;
	buf = ft_strnew(ft_get_max_len(file_l));
	while (file_l && i < file_l->content_size - 1)
	{
		c = ((char*)file_l->content)[i];
		while (file_l && i < file_l->content_size - 1
					&& c == ((char*)file_l->content)[i])
			file_l = file_l->next;
		if (file_l != NULL)
			break ;
		buf[j++] = c;
		i++;
		file_l = save;
	}
	if (ft_strlen(buf) != 0)
		return (buf);
	free(buf);
	return (NULL);
}

char				*ft_complete(t_list *file_l, char *filename)
{
	int				i;
	int				len;
	char			*ret;

	i = 0;
	len = ft_strlen(filename);
	while (i < len)
	{
		ft_delcur(&file_l, i, filename);
		i++;
	}
	if (file_l)
	{
		if ((ret = ft_chk_list(file_l, filename)) != NULL)
		{
			ft_list_clear(&file_l);
			free(filename);
			return (ret);
		}
		if (file_l && !(file_l->next))
			return (NULL);
		return (ft_select(file_l, filename));
	}
	return (NULL);
}
