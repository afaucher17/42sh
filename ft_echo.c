/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 17:25:52 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 20:40:19 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int					ft_isinbase(char *str, int basenb)
{
	static const char		*base = "0123456789ABCDEF";
	char					*sub;
	int						i;

	i = 0;
	sub = ft_strsub(base, 0, basenb);
	while (str[i] && ft_strchr(sub, ft_toupper(str[i])))
		i++;
	free(sub);
	return (i);
}

static int					ft_special_echo(char *cmd)
{
	char					*sub;
	int						size;
	int						c;
	int						base;
	int						sublen;

	size = 0;
	sublen = 0;
	sublen = ft_strnequ("\\0", cmd, 2) ? 3 : sublen;
	sublen = ft_strnequ("\\x", cmd, 2) ? 2 : sublen;
	sublen = ft_strnequ("\\U", cmd, 2) ? 8 : sublen;
	sublen = ft_strnequ("\\u", cmd, 2) ? 4 : sublen;
	if (sublen)
	{
		base = ft_strnequ("\\0", cmd, 2) ? 8 : 16;
		sub = ft_strsub(cmd, 2, sublen);
		c = ft_atoi_base(sub, base);
		size = 2 + ft_isinbase(sub, base) - 1;
		if (ft_strnequ("\\0", cmd, 2) || ft_strnequ("\\x", cmd, 2))
			ft_putchar(c);
		else
			ft_itoutf(c);
		free(sub);
	}
	return (size);
}

static void					ft_putstr_echo(char *cmd)
{
	static const char		*t[10][2] = {
		{"\\a", "\a"}, {"\\b", "\b"}, {"\\e", "\e"},
		{"\\E", "\E"}, {"\\f", "\f"}, {"\\n", "\n"}, {"\\r", "\r"},
		{"\\t", "\t"}, {"\\v", "\v"}, {"\\\\", "\\"}
	};
	int						size;
	int						i;

	while (*cmd)
	{
		i = -1;
		size = 1;
		while (++ i < 10)
			if (ft_strnequ(cmd, t[i][0], 2))
			{
				size = 2;
				ft_putstr(t[i][1]);
			}
		size += ft_special_echo(cmd);
		if (size == 1)
			ft_putchar(*cmd);
		cmd += size;
	}
}

static int					ft_getoptions(char **cmd, int *res)
{
	static const char		*op = "neE";
	int						i;
	int						j;

	i = 1;
	while (cmd[i])
	{
		j = 1;
		if (cmd[i][0] == '-')
		{
			while (cmd[i][j])
			{
				if (ft_strchr(op, cmd[i][j]))
					res[ft_strchr(op, cmd[i][j]) - op] = 1;
				else
					return (i - 1);
				j++;
			}
		}
		else
			return (i - 1);
		i++;
	}
	return (i - 1);
}

int							ft_echo(char **cmd, t_mlist *mlist)
{
	int						i;
	int						op[3] = {0, 0, 0};

	(void)mlist;
	i = 1 + ft_getoptions(cmd, op);
	while (cmd[i])
	{
		if (!op[2])
			ft_putstr_echo(cmd[i]);
		else
			ft_putstr(cmd[i]);
		if (cmd[i + 1])
			ft_putstr(" ");
		i++;
	}
	if (!op[0])
		ft_putchar('\n');
	return (1);
}
