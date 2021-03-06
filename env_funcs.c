/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:04:19 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 05:03:50 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Fonction pour creer des variables d'environnement
**	Le premier maillon de la liste est cree si la liste
**	est nulle, sinon il est ajoute a la fin de celle-ci
**	Ex : t_env *env;
**		 env = add_env(env, "$USER", "username", 1);
**		 env = addadd_env(env, "$PWD", "/home", 1);
*/

int		add_env(char *name, char *value)
{
	t_env	*save;
	t_env	*new;

	save = g_env;
	if (get_env(name))
	{
		actualise_env(name, value);
		return (0);
	}
	if (!(new = malloc(sizeof(t_env))))
		return (1);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (g_env == NULL)
	{
		g_env = new;
		return (0);
	}
	while (g_env->next != NULL)
		g_env = g_env->next;
	g_env->next = new;
	g_env = save;
	return (0);
}

int		init_env(char *envp[])
{
	char	*value;
	char	*name;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = ft_substr(envp[i], 0, j);
		value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
		add_env(name, value);
		free(name);
		free(value);
		i++;
	}
	add_env("PIPESTATUS", "0");
	return (0);
}

t_env	*get_env(char *name)
{
	t_env *tmp;

	tmp = g_env;
	if (!name || !tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_value(char *name)
{
	t_env *tmp;

	tmp = g_env;
	if (!name || !tmp || !name[0])
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	*free_all_env(void)
{
	t_env	*tmp;

	while (g_env)
	{
		free(g_env->name);
		free(g_env->value);
		tmp = g_env->next;
		free(g_env);
		g_env = tmp;
	}
	return (g_env);
}
