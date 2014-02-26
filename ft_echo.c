/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 17:25:52 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/26 18:45:02 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			ft_echo(char **cmd, t_list **env)
{
	int		i;

	(void)env;
	i = (cmd[1] && ft_strequ(cmd[1], "-n")) ? 2 : 1;
	while (cmd[i])
	{
		ft_putstr(cmd[i]);
		if (cmd[i + 1])
			ft_putstr(" ");
		i++;
	}
	if (!(cmd[1] && ft_strequ(cmd[1], "-n")))
		ft_putchar('\n');
	return (1);
}
