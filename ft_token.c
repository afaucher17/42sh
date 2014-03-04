/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 21:39:01 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/04 11:22:29 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int				ft_token_clear(t_token **list)
{
	t_token		*next;

	while (*list)
	{
		next = (*list)->next;
		free((*list)->data);
		free(*list);
		*list = next;
	}
	return (1);
}

char			ft_tokenstep(t_token **list)
{
	if ((*list)->next == NULL)
		return (0);
	*list = (*list)->next;
	return (1);
}

static t_token	*ft_tokennew(char *data, char type)
{
	t_token		*new;

	if ((new = (t_token*)malloc(sizeof(t_token))) == NULL)
		return (NULL);
	new->next = NULL;
	new->data = data;
	new->type = type;
	return (new);
}

t_token			*ft_tokenpushback(t_token **token, char *data, char type)
{
	t_token		*new;
	t_token		*cur;

	new = ft_tokennew(data, type);
	cur = *token;
	if (!token || !*token)
		*token = new;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (new);
}

t_token			*ft_token_split(char *s, char *special)
{
	char		*buff;
	int			i;
	t_token		*last;
	t_token		*list;

	list = NULL;
	buff = ft_strnew(ft_strlen(s));
	i = 0;
	while (s && *s)
		if (ft_strchr(special, *s))
		{
			if (buff[0] && !list)
				last = ft_tokenpushback(&list, ft_strdup(buff), WORD);
			else if (buff[0])
				last = ft_tokenpushback(&last, ft_strdup(buff), WORD);
			ft_bzero(buff, i);
			i = 0;
			s++;
		}
		else
			buff[i++] = *s++;
	free(buff);
	return (list);
}
