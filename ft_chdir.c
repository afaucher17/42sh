/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 13:50:40 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/04 14:08:27 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

int				ft_chdir(char *split)
{
	if (!access(split, F_OK))
	{
		if (!access(split, X_OK))
		{
			chdir(split);
			return (1);
		}
		ft_putstr_fd(split, 2);
		ft_putendl_fd(": Permission denied.", 2);
		return (0);
	}
	ft_putstr_fd(split, 2);
	ft_putendl_fd(": No such file or directory.", 2);
	return (0);
}
