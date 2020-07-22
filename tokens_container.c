/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:34:55 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/22 22:25:10 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokens_container(t_list *tokens_list)
{
	t_list	*token;
	t_fds	*fds;
	int		status;
	char	*tmp;

	if (tokens_list == NULL)
		return (0);
	fds = init_fds();
	if (!(token = get_first_token(tokens_list)))
		return (0);
	status = g_exec_token[((t_token *)token->content)->type](token, fds);
	wait(&status);
	if (status == -1)
	{
		add_env("PIPESTATUS", (tmp = ft_itoa(WEXITSTATUS(status))));
		free(tmp);
	}
	close(fds->save_stdin);
	close(fds->save_stdout);
	free(fds);
	return (0);
}
