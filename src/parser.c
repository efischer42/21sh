/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:17:27 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 14:10:16 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_readline.h"

extern char	*g_grammar[NB_TOKEN];

static int			check_next_token(enum e_token type, enum e_token *enum_tab)
{
	enum e_token	token_index;
	int				ret;

	ret = FAILURE;
	token_index = 0;
	if (enum_tab != NULL)
	{
		while (enum_tab[token_index] != NONE)
		{
			if (type == enum_tab[token_index])
			{
				ret = SUCCESS;
				break ;
			}
			token_index++;
		}
	}
	return (ret);
}

static void			merge_list(t_list *lst1, t_list *lst2)
{
	t_list	*tmp;

	if (lst2 != NULL)
	{
		tmp = lst2->next;
		ft_lstdelone(&lst1->next, &del);
		ft_lstdelone(&lst2, &del);
		lst1->next = tmp;
	}
}

static int			subprompt(t_list *lst, enum e_token *enum_tab)
{
	t_list	*new_lst;
	char	*tmp;
	int		ret;

	ret = FAILURE;
	new_lst = NULL;
	if (((t_token*)(lst->content))->type == PIPE
		|| ((t_token*)(lst->content))->type == AND_IF
		|| ((t_token*)(lst->content))->type == OR_IF)
	{
		tmp = ft_readline("> ");
		ret = lexer(tmp, &new_lst);
		if (ret == SUCCESS)
		{
			merge_list(lst, new_lst);
			ret = check_next_token(((t_token*)(lst->next->content))->type,
						enum_tab);
		}
		ft_strdel(&tmp);
	}
	return (ret);
}

static void			parse_error(int ret, enum e_token curr_type,
							t_list *lst)
{
	char	*value;

	if (ret == FAILURE)
	{
		value = ((t_token*)(lst->content))->value;
		ft_dprintf(2, "\n21sh: syntax error near unexpected token `%s'%s%s\n",
			g_grammar[curr_type], curr_type < 14 ? "" : " -> ",
			curr_type < 14 ? "" : value);
	}
}

int					parser(t_list *lst)
{
	static enum e_token	**enum_tab = NULL;
	enum e_token		curr_type;
	enum e_token		prev_type;
	int					ret;

	ret = SUCCESS;
	if (enum_tab == NULL)
		enum_tab = init_enum_tab();
	while (lst->next != NULL)
	{
		prev_type = ((t_token*)(lst->content))->type;
		curr_type = ((t_token*)(lst->next->content))->type;
		ret = check_next_token(curr_type, enum_tab[prev_type]);
		if (ret == FAILURE && curr_type == NEWLINE)
		{
			ret = subprompt(lst, enum_tab[prev_type]);
			curr_type = ((t_token*)(lst->next->content))->type;
			continue ;
		}
		if (ret == FAILURE)
			break ;
		lst = lst->next;
	}
	parse_error(ret, curr_type, lst);
	return (ret);
}
