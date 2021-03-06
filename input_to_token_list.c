/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 16:27:02 by user42            #+#    #+#             */
/*   Updated: 2020/07/25 05:00:18 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list					*ft_split1(char *s, unsigned int i,
											unsigned int j)
{
	char			q;
	t_list			*l;

	l = NULL;
	q = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == 32 && q == 0)
			i++;
		j = i;
		while (s[i] != '\0' && (s[i] != 32 || (s[i] == 32 && q != 0)))
		{
			quotes_onoff(&q, s[i]);
			i++;
		}
		if ((s[i] == 32 && q == 0) || (s[i] == '\0' && s[i - 1] != 32))
			ft_lstadd_back(&l, ft_lstnew(ft_substr(s, j, (i - j))));
	}
	if (q != 0)
	{
		ft_dsplerr(NULL, "syntax error: open quotes");
		ft_lstclear(&l, free);
		return (NULL);
	}
	return (l);
}

const char						*g_symbols_strs[6] = {
	">>",
	">",
	"<",
	"|",
	";",
	NULL
};

static int						there_is_an_operator(const char *s,
								unsigned int *i, unsigned int *j)
{
	char			q;
	unsigned int	x;

	q = 0;
	*i = -1;
	while (s[++(*i)])
	{
		quotes_onoff(&q, s[*i]);
		if (q == 0 && ft_index(CMP_SYMBOLS, s[*i]) != -1 &&
			(*i == 0 || s[*i - 1] != '\\'))
		{
			x = -1;
			while (g_symbols_strs[++x])
			{
				*j = ft_strlen(g_symbols_strs[x]);
				if (ft_strncmp(&s[*i], g_symbols_strs[x], *j) == 0)
				{
					*j = *i + *j;
					return (1);
				}
			}
		}
	}
	return (0);
}

static void						ft_split2(t_list **l, unsigned int i,
											unsigned int j)
{
	char			*s;
	t_list			*current;

	current = *l;
	while (current && (s = current->content))
	{
		if (there_is_an_operator(s, &i, &j))
		{
			if (i != 0)
			{
				ft_lstinsert(current, ft_lstnew(ft_substr(s, i, (j - i))));
				if (s[j] != 0)
					ft_lstinsert(current->next, ft_lstnew(ft_substr(s, j,
					ft_strlen(s))));
				s[i] = 0;
			}
			else if (s[j] != 0)
			{
				ft_lstinsert(current, ft_lstnew(ft_substr(s, j,
				ft_strlen(s))));
				s[j] = 0;
			}
		}
		current = current->next;
	}
}

static	t_add_token_function	g_add_token[6] = {
	add_command_token, add_redirection_token, add_redirection_token,
	add_redirection_token, add_pipe_token, add_semicolon_token
};

static t_list					*to_tokens(t_list **lst)
{
	t_list			*t;
	t_list			*l;
	t_token			*current_cmd;
	unsigned int	type;

	t = NULL;
	l = *lst;
	current_cmd = NULL;
	while (l)
	{
		type = ft_tabindex(g_symbols_strs, l->content) + 1;
		if (g_add_token[type](&t, &l, &current_cmd) == NULL)
		{
			ft_lstclear(&t, &ft_token_free);
			ft_lstclear(lst, free);
			return (NULL);
		}
		l = l->next;
	}
	ft_lstclear(lst, free);
	return (t);
}

t_list							*input_to_token_list(char *input)
{
	t_list	*l;

	if ((l = ft_split1(input, 0, 0)) == NULL)
		return (NULL);
	ft_split2(&l, 0, 0);
	l = to_tokens(&l);
	if (l == NULL)
		add_env("PIPESTATUS", SYNTAX_ERROR_CODE);
	return (l);
}
