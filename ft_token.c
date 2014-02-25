/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 21:39:01 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/04 15:44:23 by tdieumeg         ###   ########.fr       */
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

void			ft_tokenpushback(t_token **token, char *data, char type)
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
}
