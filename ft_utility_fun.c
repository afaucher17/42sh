/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 17:07:08 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/27 15:03:47 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include				"42sh.h"

t_winsize				*ft_get_winsz(void)
{
	static t_winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return (&ws);
}

t_copy					*ft_get_copy(void)
{
	static t_copy		*copy = NULL;

	if (copy == NULL)
	{
		if ((copy = (t_copy*)malloc(sizeof(t_copy))) == NULL)
			return (NULL);
		copy->copy = NULL;
		copy->visual_mode = 0;
		copy->start = 0;
	}
	return (copy);
}

char			*ft_insertchar(char c, char *cmd, int idx)
{
	char		*new;
	int			i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(cmd) + 2);
	while (i < idx)
	{
		new[i] = cmd[i];
		i++;
	}
	new[i] = c;
	i++;
	while (cmd[i])
	{
		new[i] = cmd[i];
		i++;
	}
	return (new);
}
