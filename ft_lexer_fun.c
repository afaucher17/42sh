/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_bis2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 14:34:16 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 19:47:19 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char					is_special(char *str)
{
	int					i;
	int					size;
	const char			*special[11] = {
		"<<", "<", ">>", ">", ";", "||", "&&", "|", " ", "\t", "\n"
	};

	i = 0;
	while (i < 11)
	{
		size = ft_strlen(special[i]);
		if (ft_strncmp(str, special[i], size) == 0)
			return (size);
		i++;
	}
	return (0);
}

void					ft_lexbquote(char **str, char *buf,
										int *i, t_token **list)
{
	*str = (*str) + 1;
	if (**str == '`' && buf[0] != '\0')
	{
		ft_tokenpushback(list, ft_strdup(buf), BQUOTE);
		ft_bzero(buf, BUFF_SIZE);
		*i = 0;
	}
	else if (**str != '`')
	{
		if (**str == '\\')
		{
			*str = (*str) + 1;
			buf[*i] = **str;
			*i = (*i) + 1;
			ft_lexbquote(str, buf, i, list);
			return ;
		}
		buf[*i] = **str;
		*i = (*i) + 1;
	}
}

void					ft_lexdquote(char **str, char *buf,
										int *i, t_token **list)
{
	*str = (*str) + 1;
	if (**str == '\"' && buf[0] == '\0' && is_special((*str) + 1))
	{
		ft_tokenpushback(list, ft_strdup(buf), WORD);
		ft_bzero(buf, BUFF_SIZE);
		*i = 0;
	}
	else if (**str != '\"')
	{
		if (**str == '\\' && (*((*str) + 1) == '\\' || *((*str) + 1) == '\"'
			|| *((*str) + 1) == '`'))
		{
			*str = (*str) + 1;
			buf[*i] = **str;
			*i = (*i) + 1;
			ft_lexdquote(str, buf, i, list);
			return ;
		}
		buf[*i] = **str;
		*i = (*i) + 1;
	}
}

void					ft_lexquote(char **str, char *buf,
										int *i, t_token **list)
{
	*str = (*str) + 1;
	if (**str == '\'' && buf[0] == '\0' && is_special((*str) + 1))
	{
		ft_tokenpushback(list, ft_strdup(buf), WORD);
		ft_bzero(buf, BUFF_SIZE);
		*i = 0;
	}
	else if (**str != '\'')
	{
		buf[*i] = **str;
		*i = (*i) + 1;
	}
}

void					ft_lexmain(char **str, char *buf,
										int *i, t_token **list)
{
	int					size;

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
		return ;
	}
	*str = (**str != '\\') ? *str : (*str) + 1;
	buf[*i] = **str;
	*i = (*i) + 1;
	*str = (*str) + 1;
}
