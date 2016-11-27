/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 18:37:38 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/03 18:43:41 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"libft.h"

int				ft_list_clear(t_list **list)
{
	t_list		*next;

	while (*list)
	{
		next = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = next;
	}
	return (1);
}
