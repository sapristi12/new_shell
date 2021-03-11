/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:50:10 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 17:02:15 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_command_nf(t_cmd *cmd, t_list **envs)
{
	char	**strs;
	char	*command;
	int 	path;

	strs = pointer_package(cmd->cmds, cmd->pipe.nb_pipe);
	command = NULL;
	command = strs[0];
	path = get_path_command(command, envs);
	if (is_builtin(command))
		return ;
	if (path && !is_builtin(command))
		return ;
	else if (!is_builtin(command) && !path)
	{
		if (g_sig == 0)
			g_sig = 127;
	}
}
