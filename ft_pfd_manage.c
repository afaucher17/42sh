/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfd_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/07 12:57:10 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/14 18:55:33 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

void		ft_pfd_manage(int *pfd, int *pfd2)
{
	if (pfd == NULL && pfd2 != NULL)
	{
		close(pfd2[0]);
		dup2(pfd2[1], 1);
	}
	if (pfd != NULL && pfd2 != NULL)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd2[0]);
		dup2(pfd2[1], 1);
	}
	if (pfd != NULL && pfd2 == NULL)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
	}
}

void		ft_pfd_close(int *pfd)
{
	if (pfd)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
}
