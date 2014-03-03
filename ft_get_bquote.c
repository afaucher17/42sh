/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_bquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 10:14:03 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/03 19:06:22 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

static void		ft_bq_son(int *pfd, t_token **bquote, t_list **env)
{
	ft_get_bquote(bquote, env);
	close(pfd[0]);
	dup2(pfd[1], 1);
	ft_compute(bquote, env);
	exit(EXIT_SUCCESS);
}

static char		*ft_bq_father(int *pfd, t_token **bquote, int pid)
{
	int			len;
	char		*tmp;
	char		*results;
	char		buf[BUFF_SIZE];
	int			i;

	close(pfd[1]);
	dup2(pfd[0], 0);
	wait(&pid);
	results = NULL;
	while ((len = read(0, buf, BUFF_SIZE - 1)) > 0)
	{
		i = 0;
		buf[len] = '\0';
		tmp = results;
		if (ft_strnequ(buf, "\033[4l", 4))
			i = 4;
		results = ft_strjoin(tmp, buf + i);
		free(tmp);
		ft_bzero(buf, BUFF_SIZE);
	}
	dup2((ft_reset_std())[0], 0);
	close(pfd[0]);
	ft_token_clear(bquote);
	return (results);
}

static t_token	*ft_if_bq(t_token **bquote, t_list **env, t_token **save)
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
		ft_bq_son(pfd, bquote, env);
	else
	{
		free(results);
		results = ft_bq_father(pfd, bquote, pid);
	}
	list = ft_token_split(results, "\n \t");
	tmp = list;
	free(results);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*save)->next;
		return (*save = list);
	}
	return (*save = (*save)->next);
}

void			ft_get_bquote(t_token **list, t_list **env)
{
	t_token     *save;
	t_token     *bquote;
	t_token		*prev;

	save = *list;
	prev = NULL;
	while (save)
	{
		bquote = NULL;
		if (save->type == BQUOTE)
		{
			ft_lexer(save->data, &bquote, 0);
			free(save->data);
			save->data = NULL;
			if (bquote)
			{
				if (prev != NULL)
					prev->next = ft_if_bq(&bquote, env, &save);
				else
					*list = ft_if_bq(&bquote, env, &save);
			}
		}
		prev = save;
		if (save)
			save = save->next;
	}
}
