/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 18:19:05 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/08 21:32:26 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static char		*ft_wait_finish(char *str)
{
	char		*buf;
	char		*complete;

	buf = ft_strnew(BUFF_SIZE);
	ft_putstr("> ");
	ft_set_term();
	buf = ft_read_keys(ft_log_to_dlist());
	ft_reset_term();
	ft_bzero(g_cmd, BUFF_SIZE);
	g_idx = 0;
	complete = ft_strjoin(str, buf);
	free(buf);
	return (complete);
}

char			*ft_analyser(char *cmd)
{
	int			i;
	int			special[6] = {0, 0, 0, 0, 0, 0};

	i = 0;
	while (cmd[i])
	{
		special[0] ^= (cmd[i] == '\"' && !special[1]);
		special[1] ^= (cmd[i] == '\'' && !special[0]);
		special[2] ^= (cmd[i] == '`' && !special[1]);
		if (!special[0] && !special[1])
		{
			special[3] -= (cmd[i] == ')');
			special[3] += (cmd[i] == '(');
			special[4] -= (cmd[i] == ']');
			special[4] += (cmd[i] == '[');
		}
		i++;
	}
	if (special[0] || special[1] || special[2]
		|| special[3] > 0 || special[4] > 0)
	{
		cmd = ft_wait_finish(cmd);
		return (ft_analyser(cmd));
	}
	return (cmd);
}
