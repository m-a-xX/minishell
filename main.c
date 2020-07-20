/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:34:08 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/14 23:49:45 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env = NULL;
/* int		(*g_exec_token[]) () = {&ft_command, &ft_r_append, &ft_r_trunc,
								&ft_r_in, &ft_pipe,
								&ft_semicolon, &ft_and, &ft_or};  */
int		(*g_builtins[]) () = {&ft_echo, &ft_pwd, &ft_cd, &ft_export,
								&ft_unset, &ft_env, &ft_exit};
int		(*g_exec_token[]) () = {&ft_command, &ft_pipe};
char	*builtins[] = {"echo", "pwd", "cd", "export", "unset", "env", "exit", NULL};

int		main(int ac, char *av[], char *envp[])
{
	char	*input;
	t_list	*lst;
	//int		i;
	//t_list *token;

	(void)ac;
	(void)av;
	init_env(envp);
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_bs);
	while (1)
	{
		prompt();
		get_next_line(0, &input);
		if (!ft_strcmp(input, "q") || !ft_strcmp(input, "exit"))
			break;
		else
		{
			lst = input_to_token_list(input);
			tokens_container(lst);
			ft_lstclear(&lst, &ft_token_free);
		}
	}
	free_all_env();
	return (0);
}
