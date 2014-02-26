/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 13:44:15 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/26 19:10:16 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static char		is_special(char *str)
{
	int			i;
	int			size;
	char		*special[12] = {
		"<<", "<", ">>", ">", ";", "`", "'", " ", "!", "\t", "|", "\n"
	};

	i = 0;
	while (i < 12)
	{
		size = ft_strlen(special[i]);
		if (ft_strncmp(str, special[i], size) == 0)
			return (size);
		i++;
	}
	return (0);
}

static char		handler_special(char **str, char *buf, int *i, t_token **list)
{
	int			size;

	if ((size = is_special(*str)) != 0)
	{
		if (buf[0] != '\0')
			ft_tokenpushback(list, ft_strdup(buf), WORD);
		ft_bzero(buf, BUFF_SIZE);
		*i = 0;
		while (*i < size && **str)
		{
			if (**str != ' ' && **str != '\t' && **str != '\n')
				buf[*i] = **str;
			*i = (*i) + 1;
			*str = (*str) + 1;
		}
		if (buf[0] != '\0')
			ft_tokenpushback(list, ft_strdup(buf), SPECIAL);
		ft_bzero(buf, BUFF_SIZE);
		*i = 0;
		return (1);
	}
	return (0);
}

static void		handler_normal(char **str, char *buf, int *i, int *inhib)
{
	if ((**str == '\"' && !inhib[1]) || (**str == '\'' && !inhib[0]))
	{
		*str = (*str) + 1;
		return ;
	}
	if (!inhib[1] && (**str == '\\') && !(inhib[0]
		&& *(*str + 1) != '\"' && *(*str + 1) != '\\'))
		*str = (*str) + 1;
	buf[*i] = **str;
	*i = (*i) + 1;
	*str = (*str) + 1;
}

void			ft_lexer(char *str, t_token **list)
{
	char		*buf;
	char		*save;
	int			i;
	int			inhib[2] = {0, 0};

	i = 0;
	save = str;
	buf = ft_strnew(BUFF_SIZE);
	while (*str)
	{
		inhib[0] ^= (*str == '\"' && !inhib[1]);
		inhib[1] ^= (*str == '\'' && !inhib[0]);
		if (inhib[0] || inhib[1] || !handler_special(&str, buf, &i, list))
			handler_normal(&str, buf, &i, inhib);
	}
	if (buf[0] != '\0')
		ft_tokenpushback(list, ft_strdup(buf), WORD);
	if (*list)
		ft_append_cmd_to_log(save);
	free(buf);
}
