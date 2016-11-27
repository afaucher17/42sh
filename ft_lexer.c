/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 13:37:20 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/27 12:07:28 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_state		ft_getstate(char **str, enum e_state state)
{
	if (state == L_MAIN && **str == '`')
		return (L_BQUOTEM);
	if (state == L_MAIN && **str == '\'')
		return (L_QUOTE);
	if (state == L_MAIN && **str == '\"')
		return (L_DQUOTE);
	if (state == L_DQUOTE && **str == '`')
		return (L_BQUOTED);
	if ((state == L_DQUOTE && **str == '\"')
		|| (state == L_QUOTE && **str == '\'')
		|| (state == L_BQUOTEM && **str == '`'))
	{
		*str = (*str) + 1;
		return (L_MAIN);
	}
	if (state == L_BQUOTED && **str == '`')
		return (L_DQUOTE);
	return (state);
}

static void	ft_lexer_init(int *i, t_state *state, char **buf)
{
	*i = 0;
	*state = L_MAIN;
	*buf = ft_strnew(BUFF_SIZE);
}

void		ft_lexer(char *str, t_token **list, int save_com)
{
	char				*buf;
	char				*save;
	t_state				state;
	int					i;

	ft_lexer_init(&i, &state, &buf);
	save = str;
	while (str && *str)
	{
		state = ft_getstate(&str, state);
		if (state == L_MAIN)
			ft_lexmain(&str, buf, &i, list);
		if (state == L_QUOTE)
			ft_lexquote(&str, buf, &i, list);
		if (state == L_DQUOTE)
			ft_lexdquote(&str, buf, &i, list);
		if (state == L_BQUOTEM || state == L_BQUOTED)
			ft_lexbquote(&str, buf, &i, list);
	}
	if (buf[0] != '\0')
		ft_tokenpushback(list, ft_strdup(buf), WORD);
	if (*list && save_com)
		ft_append_cmd_to_log(save);
	free(buf);
}
