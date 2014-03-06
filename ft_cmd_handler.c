/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 14:46:12 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/05 17:21:25 by tdieumeg         ###   ########.fr       */
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

static void		ft_son(int builtin, char **cmd, char **charenv)
{
	t_list		*envdup;

	signal(SIGINT, SIG_DFL);
	if (!cmd)
		exit(EXIT_SUCCESS);
	if (!builtin)
	{
		ft_reset_term();
		execve(cmd[0], cmd, charenv);
		ft_notfnd(cmd[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		envdup = ft_duplicate(charenv);
		ft_builtin(cmd, &envdup);
		ft_list_clear(&envdup);
	}
	exit(EXIT_SUCCESS);
}

static int		ft_father(int *pfd, char ***cmd, char ***charenv,
							t_list **fdlist)
{
	int			waitvar;

	waitvar = 0;
	signal(SIGINT, ft_sighand2);
	signal(SIGUSR1, ft_sighandler);
	ft_pfd_close(pfd);
	wait(&waitvar);
	ft_close_fdlist(fdlist);
	ft_clear_tab(*cmd);
	ft_clear_tab(*charenv);
	if (WIFSIGNALED(waitvar))
		return (0);
	return (!WEXITSTATUS(waitvar));	
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
	builtin = ft_is_builtin(tree->data);
	if (!builtin)
		cmd = ft_arg_handler(tree, ft_checkpath(tree->data, charenv));
	else
		cmd = ft_arg_handler(tree, ft_strdup(tree->data));
	if ((pid = fork()) < 0)
		return (0);
	if (pid == 0)
	{
		ft_pfd_manage(pfd, pfd2);
		ft_red_handler(tree->left, &fdlist);
		ft_son(builtin, cmd, charenv);
	}
	else
		return (ft_father(pfd, &cmd, &charenv, &fdlist));
	return (0);
}


