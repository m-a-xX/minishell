/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:34:08 by mavileo           #+#    #+#             */
/*   Updated: 2020/06/27 04:32:27 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *env = NULL;

int		main(int ac, char *av[], char *envp[])
{
	char *input;

	init_env();
	ft_exit(av);
	//prompt();
	//get_next_line(0, &input);
	return (0);
}
