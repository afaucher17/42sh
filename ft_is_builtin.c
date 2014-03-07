/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 11:57:10 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/07 13:30:39 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

int				ft_is_builtin(char *cmd)
{
	int			i;
	char		*builtin[6] = {
		"exit", "unsetenv", "setenv", "env", "cd", "echo"};

	if (!cmd)
		return (0);
	i = 0;
	while (i < 6)
	{
		if (ft_strequ(cmd, builtin[i]))
			return (1);
		i++;
	}
	return (0);
}
