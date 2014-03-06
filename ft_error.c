/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 16:46:20 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/05 16:51:58 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		ft_error(char *filename, char *error)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}
