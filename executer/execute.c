#include "../minishell.h"

int	create_pid_arr(t_menu *menu)
{
	int		i;
	t_cmds	*cmds;

	i = 0;
	cmds = *(menu->cmds);
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	if (i == 0)
		menu->pid_arr = NULL;
	else
		menu->pid_arr = (int *)malloc(sizeof(int) * (i + 1));
	menu->pid_arr[i] = 0;
	return (i);
}

void	pipe_utils_parent(int *fds)
{
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
}

int	pipe_utils_child(t_menu *menu, t_cmds *cmd, int *fds, t_cmds **cmds)
{
	menu->is_child = 1;
	signal(SIGINT, SIG_DFL);
	*cmds = cmd;
	if (!cmd->next)
	{
		dup2(menu->fd_out, STDOUT_FILENO);
		close(menu->fd_out);
		return (0);
	}
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(fds[0]);
	return (0);
}

int	handle_pipes(t_cmds **cmds, t_menu *menu)
{
	int		i;
	int		fds[2];
	t_cmds	*cmd;

	i = 0;
	cmd = *cmds;
	while (cmd)
	{
		pipe(fds);
		if ((menu->pid_arr[i++] = fork()) != 0)
		{
			pipe_utils_parent(fds);
			cmd = cmd->next;
			if (!cmd)
				return (dup2(menu->fd_in, STDIN_FILENO), close(fds[1]), 1);
		}
		else
			return (pipe_utils_child(menu, cmd, fds, cmds));
	}
	return (0);
}

int	handle_is_dir_er(t_menu *menu)
{
	write_error_message("Is a directory\n");
	if (menu->is_child)
	{
		free_mid_process(menu);
		exit(127);
	}
	return (menu->return_code = 127, 1);
}

int	handle_acess_file_er(t_menu *menu)
{
	//write_error_message(" Permission denied\n");
	if (menu->is_child)
	{
		free_mid_process(menu);
		exit(1);
	}
	return (menu->return_code = 1, 1);
}

int	handle_red_out(t_menu *menu, t_args *temp, int fd_out)
{
	fd_out = open(temp->token, O_RDWR | O_CREAT, 0777);
	if (check_dir(temp->token) == 2)
		if (handle_is_dir_er(menu))
			return (1);
	if (!check_acess_file(temp->token, 2, menu))
		if (handle_acess_file_er(menu))
			return (1);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int	handle_red_app(t_menu *menu, t_args *temp, int fd_out)
{
	fd_out = open(temp->token, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (check_dir(temp->token) == 2)
		if (handle_is_dir_er(menu))
			return (1);
	if (!check_acess_file(temp->token, 2, menu))
		if (handle_acess_file_er(menu))
			return (1);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int	handle_red_in(t_menu *menu, t_args *temp, int fd_in)
{
	fd_in = open(temp->token, O_RDWR, 0777);
	if (check_dir(temp->token) == 2)
		if (handle_is_dir_er(menu))
			return (1);
	if (!check_acess_file(temp->token, 1, menu))
		if (handle_acess_file_er(menu))
			return (1);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (0);
}

int	handle_redirs(t_cmds *cmd, t_menu *menu)
{
	int		fd_out;
	int		fd_in;
	t_args	*temp;

	fd_out = STDOUT_FILENO;
	fd_in = STDIN_FILENO;
	temp = cmd->redir;
	while (temp)
	{
		if (temp->type == RED_OUT)
		{
			if (handle_red_out(menu, temp, fd_out))
				return (1);
		}
		else if (temp->type == APP_OUT)
		{
			if (handle_red_app(menu, temp, fd_out))
				return (1);
		}
		else if (temp->type == RED_IN)
		{
			if (handle_red_in(menu, temp, fd_in))
				return (1);
		}
		else if (temp->type == HERE_DOC)
		{
			dup2(cmd->here_fds[0], STDIN_FILENO);
			close(cmd->here_fds[0]);
		}
		temp = temp->next;
	}
	return (0);
}

char	*get_command_path(t_cmds *cmds, t_menu *menu)
{
	char	**possible_paths;
	char	*path;
	int		i;

	i = 0;
	possible_paths = NULL;
	possible_paths = ft_split(path = env_get("PATH", menu), ':');
	free(path);
	while (possible_paths && possible_paths[i])
	{
		path = ft_strjoin(possible_paths[i], "/");
		path = ft_strjoin_free(path, cmds->cmd);
		if (!access(path, F_OK))
		{
			ft_free_matrix(possible_paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_matrix(possible_paths);
	write_error_message(cmds->cmd);
	write_error_message(": command not found\n");
	free_mid_process(menu);
	exit(127);
}

void	exe_3(t_menu *menu, t_cmds *cmds, int *result)
{
	char	*path;

	if (!ft_strncmp(cmds->cmd, "/", 1) || !ft_strncmp(cmds->cmd, "./", 2))
		path = ft_strdup(cmds->cmd);
	else
		path = get_command_path(cmds, menu);
	*result = execve(path, cmds->args , menu->env);
	free(path);
}

void	exe_2(t_menu *menu, t_cmds *cmds)
{
	int	result;

	result = 0;
	if (cmds->cmd)
		exe_3(menu, cmds, &result);
	if (errno == EACCES)
	{
		if (check_dir(cmds->cmd) == 2)
			{
				result = 126;
				write_error_message(cmds->cmd);
				write_error_message(": Is a directory\n");
			}
		else
		{
			result = 126;
			write_error_message(cmds->cmd);
			write_error_message(": Permission denied\n");
		}
	}
	else if (errno == ENOENT)
	{
		if (!ft_strncmp(cmds->cmd, "/", 1) || !ft_strncmp(cmds->cmd, "./", 2))
		{
			if (check_dir(cmds->cmd) == 2)
			{
				result = 126;
				write_error_message(cmds->cmd);
				write_error_message(": Is a directory\n");
			}
			else
			{
				result = 127;
				write_error_message(cmds->cmd);
				write_error_message(": No such file or directory\n");
			}
		}
	}
	else
		result = 1;
	free_mid_process(menu);
	exit(result);
}
void	process_handler(t_menu *menu)
{
	t_cmds *cmds;

	cmds = *(menu->cmds);
	
	if (create_pid_arr(menu) == 1 && ft_is_built(cmds))
		return (free(menu->pid_arr), menu->pid_arr = NULL, handle_builts(cmds, menu), reset_ouput(menu));
	if (handle_pipes(&cmds, menu))
		return ;
	handle_builts(cmds, menu);
	if (cmds->cmd && !cmds->cmd[0])
	{
		free_mid_process(menu);
		exit(0);
	}
	exe_2(menu, cmds);
}