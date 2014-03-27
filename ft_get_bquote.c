/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_bquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 10:14:03 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/27 12:59:08 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"sh42.h"

static void		ft_bq_son(int *pfd, t_token **bquote, t_mlist *mlist)
{
	ft_get_bquote(bquote, mlist);
	close(pfd[0]);
	dup2(pfd[1], 1);
	ft_compute(bquote, mlist);
	exit(EXIT_SUCCESS);
}

static char		*ft_bq_father(int *pfd, t_token **bquote)
{
	int			len;
	char		*tmp;
	char		*results;
	char		buf[BUFF_SIZE];

	close(pfd[1]);
	dup2(pfd[0], 0);
	results = NULL;
	while ((len = read(0, buf, BUFF_SIZE - 1)) > 0)
	{
		buf[len] = '\0';
		tmp = results;
		results = ft_strjoin(tmp, buf);
		free(tmp);
		ft_bzero(buf, BUFF_SIZE);
	}
	while ((wait(NULL)) >= 0)
		;
	dup2((ft_reset_std())[0], 0);
	close(pfd[0]);
	ft_token_clear(bquote);
	return (results);
}

static t_token	*ft_if_bq(t_token **bquote, t_mlist *mlist, t_token **save,
							t_token *next)
{
	int			pid;
	int			pfd[2];
	char		*results;
	t_token		*list;
	t_token		*tmp;

	pipe(pfd);
	pid = fork();
	results = NULL;
	if (pid == 0)
		ft_bq_son(pfd, bquote, mlist);
	else
		results = ft_bq_father(pfd, bquote);
	list = ft_token_split(results, "\n \t");
	tmp = list;
	free(results);
	free(*save);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = next;
		return (*save = list);
	}
	return (*save = next);
}

void			ft_get_bquote(t_token **list, t_mlist *mlist)
{
	t_token		*save;
	t_token		*bquote;
	t_token		*prev;

	save = *list;
	prev = NULL;
	while (save)
	{
		bquote = NULL;
		if (save->type == BQUOTE)
		{
			ft_lexer(save->data, &bquote, 0);
			ft_strdel(&(save->data));
			if (prev != NULL)
				prev->next = (bquote) ?
					ft_if_bq(&bquote, mlist, &save, save->next) : NULL;
			else
				*list = (bquote) ?
					ft_if_bq(&bquote, mlist, &save, save->next) : NULL;
		}
		prev = save;
		if (save)
			save = save->next;
	}
}
