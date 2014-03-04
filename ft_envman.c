/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 15:05:05 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/04 12:09:17 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

t_list				*ft_duplicate(char **environ)
{
	t_list			*env;
	int				i;

	env = NULL;
	i = 0;
	while (environ[i])
	{
		ft_lstpushback(&env, environ[i], ft_strlen(environ[i]) + 1);
		i++;
	}
	return (env);
}

char				**ft_tochar(t_list *env)
{
	int				i;
	t_list			*tmp;
	char			**envir;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envir = (char**)malloc(sizeof(char*) * (i + 1));
	i = 0;
	while (env)
	{
		envir[i] = ft_strdup((char*)env->content);
		i++;
		env = env->next;
	}
	envir[i] = NULL;
	return (envir);
}
