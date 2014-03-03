/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 17:25:52 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/03 12:05:18 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			ft_echo(char **cmd, t_list **env, t_node *tree, t_list **list)
{
	int		i;

	(void)tree;
	(void)env;
	ft_red_handler(tree->left, list);
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
	dup2((ft_reset_std())[0], 0);
	dup2((ft_reset_std())[1], 1);
	ft_close_fdlist(list);
	return (1);
}
