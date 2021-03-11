#include "minishell.h"

void 	command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(" : command not found\n", STDERR_FILENO);
}

static int 	is_slash(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int		ft_dir(char *path, char *exec)
{
	DIR				*dir;
	struct dirent	*my_dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	my_dir = readdir(dir);
	while (my_dir != NULL)
	{
		if (!ft_strcmp(my_dir->d_name, exec))
			return ((closedir(dir) * 0) + 1);
		my_dir = readdir(dir);
	}
	closedir(dir);
	return (0);
}

int 	get_path_command(char *command, t_list **envs)
{
	char	**path;
	char	*whole_path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	if (!(whole_path = get_env(*envs, "PATH")))
		return (0);
	if (!(path = new_split(whole_path, ':')))
		return (0);
	while (path[i] && !ft_dir(path[i], command))
		i++;
	if (path[i] != NULL && ft_dir(path[i], command) != -1)
	{
		//tmp = ft_stradd(path[i], "/");
		//tmp2 = ft_stradd(tmp, command);
		//free(tmp);
		free_char_double_array(path);
		return (1);
	}
	free_char_double_array(path);
	return (0);
}

int 	is_dir(char *cmd)
{
	DIR		*dir;

	dir = opendir(cmd);
	if (!dir)
		return (0);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(" : is a directory\n", STDERR_FILENO);
	closedir(dir);
	return (1);
}

void 	is_not_found(char *cmd, char **envp)
{
	t_list	*envs;

	if (!(envs = init_list_env(envp)))
		return ;
	if (!get_env(envs, "PATH"))
		perror("minishell");
	else if (!ft_strcmp(cmd, ".."))
		command_not_found(cmd);
	else if (is_slash(cmd))
	{
		if (!is_dir(cmd))
			perror("minishell");
	}
	else
	{
		if (!(get_path_command(cmd, &envs)))
			command_not_found(cmd);
	}
}