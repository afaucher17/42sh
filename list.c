/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 21:20:06 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 12:17:47 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_select.h"
#include "libft.h"

static t_lst	*new_elem(char *label)
{
	t_lst	*new;

	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	new->label = ft_strdup(label);
	new->length = (new->label) ? ft_strlen(label) : 0;
	new->selected = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void			lst_pushback(t_lst **list, char *str)
{
	t_lst	*current;
	t_lst	*new;

	if (!(new = new_elem(str)))
		return ;
	else if (!(*list))
		*list = new;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
}

void			lst_free(t_lst **list)
{
	if (!*list)
		return ;
	lst_free(&((*list)->next));
	free((*list)->label);
	free(*list);
	*list = NULL;
}

void			lst_delelem(t_select *slct)
{
	t_lst	*current;

	if (slct->list)
	{
		current = slct->current;
		if (current->next)
			current->next->prev = (current->prev) ? current->prev : NULL;
		if (current->prev)
			current->prev->next = (current->next) ? current->next : NULL;
		else
			slct->list = current->next;
		free(current);
	}
}

t_lst			*fill_list(t_lst **list, int ac, char **av)
{
	int		i;

	i = 1;
	while (++i <= ac)
		lst_pushback(list, av[i - 1]);
	return (*list);
}
