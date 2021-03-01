/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:14:55 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:45:42 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_tab(t_cmd *cmd)
{
	int j;
	int pointer;

	pointer = 0;
	j = 0;
	cmd->tab = malloc(sizeof(int *) * (cmd->pipe.nb_pipe + 1));
	if (!cmd->tab)
		return (0);
	while (j < cmd->pipe.nb_pipe + 1)
	{
		if (!(cmd->tab[j] = create_tab_index(&(cmd->cmds[pointer]))))
			return (0);
		pointer += move_pointer_i(&(cmd->cmds[pointer]));
		j++;
	}
	return (1);
}

int		init_space(t_space *space, char *str)
{
	space->j = 0;
	space->in_quote = -1;
	space->size = get_size(str) + ft_strlen(str);
	space->dest = malloc(space->size + 1);
	if (!space->dest)
		return (0);
	space->dest[space->size] = '\0';
	return (1);
}

void	init_struct_pipe(t_pipe *pipe)
{
	pipe->nb_pipe = 0;
	pipe->save = 0;
	pipe->all = NULL;
	pipe->fd = NULL;
	pipe->fd_saved = 0;
	pipe->pid = 0;
}

void	init_struct_cmd(t_cmd *cmd)
{
	cmd->cmds = NULL;
	cmd->mystdin = dup(STDIN_FILENO);
	cmd->mystdout = dup(STDOUT_FILENO);
	cmd->exit_status[0] = 0;
	cmd->tabsize = 0;
	cmd->tab = NULL;
	cmd->exit_status[0] = -99;
	init_struct_pipe(&cmd->pipe);
}
