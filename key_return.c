/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slct_key_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 19:02:22 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 14:29:41 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_select.h"
#include "libft.h"

void	slct_key_return(t_select *slct, int *pfd)
{
	t_lst	*list;

	list = slct->current;
	dup2(pfd[1], 1);
	if (!list)
		proper_exit(EXIT_SUCCESS);
	write(1, list->label, list->length);
	proper_exit(EXIT_SUCCESS);
}
