/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 13:44:15 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/25 18:20:28 by tdieumeg         ###   ########.fr       */
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

static char		*ft_wait_finish(char *str, t_dlist *stack)
{
	char		*buf;
	char		*complete;

	buf = ft_strnew(BUFF_SIZE);
	ft_putstr("> ");
	buf = ft_read_keys(stack);
	ft_bzero(g_cmd, BUFF_SIZE);
	g_idx = 0;
	complete = ft_strjoin(str, buf);
	free(buf);
	return (complete);
}

void			ft_lexer(char *str, t_dlist *stack, int *inhib, t_token **list)
{
	char		*buf;
	int			i;

	i = 0;
	buf = ft_strnew(BUFF_SIZE);
	while (*str)
	{
		inhib[0] ^= (*str == '\"' && !inhib[1]);
		inhib[1] ^= (*str == '\'' && !inhib[0]);
		if (!inhib[0] && !inhib[1])
		{
			inhib[2] -= (*str == ')');
			inhib[2] += (*str == '(');
		}
		if (inhib[0] || inhib[1] || !handler_special(&str, buf, &i, list))
			handler_normal(&str, buf, &i, inhib);
	}
	if (inhib[0] || inhib[1] || inhib[2] > 0)
	{
		buf = ft_wait_finish(buf, stack);
		ft_lexer(buf, stack, inhib, list);
	}
	else if (buf[0] != '\0')
		ft_tokenpushback(list, ft_strdup(buf), WORD);
	free(buf);
}
