/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:08:26 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 15:58:01 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		condition(char *content, char *str)
{
	if (!ft_strncmp(content, str, ft_strlen(str))
	&& content[ft_strlen(str)] == '=')
	{
		return (1);
	}
	return (0);
}

void			ft_delone(t_list **lst, char *str)
{
	t_list	*envs;
	t_list	*tmp;

	envs = *lst;
	if (condition(envs->content, str))
	{
		tmp = envs->next;
		free(envs->content);
		free(envs);
		*lst = tmp;
		return ;
	}
	while (envs)
	{
		if (!ft_strncmp(envs->content, str, ft_strlen(str))
		&& envs->content[ft_strlen(str)] == '=')
		{
			tmp->next = envs->next;
			free(envs->content);
			free(envs);
			envs = tmp;
		}
		tmp = envs;
		envs = envs->next;
	}
}

int				ft_unset(t_cmd *cmd, t_list **envs)
{
	int i;

	i = 1;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
	{
		if (cmd->cmds[i][0] == '/')
			error_identifier(cmd->cmds[i]);
		else
			ft_delone(envs, cmd->cmds[i]);
		i++;
	}
	return (1);
}
