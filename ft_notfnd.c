/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notfnd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 12:32:34 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/04 14:09:43 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

void			ft_notfnd(char *split)
{
	ft_putstr_fd("ft_sh3: command not found: ", 2);
	ft_putendl_fd(split, 2);
}
