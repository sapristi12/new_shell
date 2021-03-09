/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:00:16 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/05 10:53:53 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		single_command(t_cmd *cmd, t_list **envs)
{
	int ret;

	if (!(parsing_redir(cmd, 0)))
		return (free_error_redir(cmd, 0));
	ret = exec_cmd(cmd, envs, 0);
	free_package(cmd);
	dup2(cmd->mystdout, STDOUT_FILENO);
	dup2(cmd->mystdin, STDIN_FILENO);
	if (ret == -1)
		return (-2);
	return (1);
}

int		several_commands(t_cmd *cmd, t_list **envs)
{
	int ret;

	cmd->mystdout = dup(STDOUT_FILENO);
	cmd->mystdin = dup(STDIN_FILENO);
	if (init_pipe(cmd) == -1)
		return (0);
	ret = loop_command_pipe(cmd, envs);
	dup2(cmd->mystdout, STDOUT_FILENO);
	dup2(cmd->mystdin, STDIN_FILENO);
	if (ret == -1)
		return (free_end_pipe(cmd, -2));
	pipe_first_command(cmd, envs);
	return (free_end_pipe(cmd, 1));
}

int		parsing_command(t_cmd *cmd, t_list **envs)
{
	if (!(check_first_command(cmd, envs)))
		return (0);
	init_all_package(cmd, envs);
	if (cmd->pipe.nb_pipe == 0)
		return (single_command(cmd, envs));
	if (cmd->pipe.nb_pipe > 0)
		return (several_commands(cmd, envs));
	return (1);
}

int		*create_tab_index(char **cmds)
{
	int		i;
	int		*tab;

	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
		i++;
	tab = malloc(sizeof(int) * i);
	if (!tab)
		return (NULL);
	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
	{
		if (!ft_strcmp(cmds[i], ">") || !ft_strcmp(cmds[i], ">>")
		|| !ft_strcmp(cmds[i], "<"))
			tab[i] = 1;
		else
			tab[i] = 0;
		i++;
	}
	return (tab);
}

int		parsing_line(char *prompt, t_list **envs, t_cmd *cmd)
{
	int		ret;

	init_struct_cmd(cmd);
	get_pid(SET, 0);
	if (!(prompt = create_space_around(prompt)))
		return (errno_parsing_line(-2));
	if (!(cmd->cmds = new_split(prompt, ' ')))
		return (errno_parsing_line(-3));
	if (!several_string(cmd->cmds))
		return (errno_parsing_line(free_i(cmd, -4)));
	if (!parsing_pipe(cmd))
		return (errno_parsing_line(free_i(cmd, -5)));
	if (!(init_tab(cmd)))
		return (0);
	if (!(parsing_quotes(cmd, envs)))
		return (errno_parsing_line(free_quote(cmd, prompt, -6)));
	g_sig = 0;
	if ((ret = parsing_command(cmd, envs)) <= 0)
		return (free_8(prompt, cmd, ret));
	if (cmd->exit_status[0] == 1)
		return (free_8(prompt, cmd, -2));
	free(prompt);
	free_char_double_array(cmd->cmds);
	free_int_double_array(cmd);
	return (0);
}
