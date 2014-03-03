/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 14:46:12 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/03 19:05:34 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

static void		ft_pfd_manage(int *pfd, int *pfd2)
{
	if (pfd == NULL && pfd2 != NULL)
	{
		close(pfd2[0]);
		dup2(pfd2[1], 1);
	}
	if (pfd != NULL && pfd2 != NULL)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd2[0]);
		dup2(pfd2[1], 1);
	}
	if (pfd != NULL && pfd2 == NULL)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
	}
}

static void		ft_pfd_close(int *pfd)
{
	if (pfd)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
}

static void		ft_son(t_node *tree, int builtin, char **cmd, char **charenv,
							t_list **fdlist)
{
	signal(SIGINT, SIG_DFL);
	if (!builtin)
	{
		ft_red_handler(tree->left, fdlist);
		ft_reset_term();
		execve(cmd[0], cmd, charenv);
		ft_notfnd(cmd[0]);
	}
	exit(EXIT_SUCCESS);
}

static void		ft_father(pid_t pid, int *pfd, char ***cmd, char ***charenv,
							t_list **fdlist)
{
	signal(SIGINT, ft_sighand2);
	ft_pfd_close(pfd);
	wait(&pid);
	ft_close_fdlist(fdlist);
	ft_clear_tab(*cmd);
	ft_clear_tab(*charenv);
}

int				ft_cmd_handler(t_node *tree, t_list **env, int *pfd, int *pfd2)
{
	pid_t		pid;
	int			builtin;
	char		**cmd;
	char		**charenv;
	t_list		*fdlist;

	fdlist = NULL;
	charenv = ft_tochar(*env);
	cmd = ft_arg_handler(tree, ft_strdup(tree->data));
	builtin = ft_builtin(cmd, env, tree, &fdlist);
	ft_clear_tab(cmd);
	cmd = NULL;
	if (!builtin)
		cmd = ft_arg_handler(tree, ft_checkpath(tree->data, charenv));
	if ((pid = fork()) < 0)
		return (0);
	if (pid == 0)
	{
		ft_pfd_manage(pfd, pfd2);
		ft_son(tree, builtin, cmd, charenv, &fdlist);
	}
	else
		ft_father(pid, pfd, &cmd, &charenv, &fdlist);
	return (1);
}
