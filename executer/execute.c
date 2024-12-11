#include "../minishell.h"


int	create_pid_arr(t_menu *menu)
{
	int		i;
	t_cmds *cmds;

	i = 0;
	cmds = *(menu->cmds);
	while(cmds)
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

void pipe_utils_parent(int *fds)
{
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
}

int pipe_utils_child(t_menu *menu, t_cmds *cmd, int *fds, t_cmds **cmds)
{
	menu->is_child = 1;
	signal(SIGINT, SIG_DFL);
	*cmds = cmd;
	if(!cmd->next)
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
	int	i;
	int	fds[2];
	t_cmds *cmd;

	i = 0;
	cmd = *cmds;
	while (cmd)
	{
		pipe(fds);
		if((menu->pid_arr[i++] = fork()) != 0)
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

void	handle_is_dir_er(t_menu *menu)
{
	free_mid_process(menu);
	write_error_message("Is a directory\n");
	exit(127);
}

void	handle_acess_file_er(t_menu *menu)
{
	free_mid_process(menu);
	write_error_message(" Permission denied\n");
	exit(1);	
}

void	handle_red_out(t_menu *menu, t_cmds *cmd, int fd_out)
{
	fd_out = open(cmd->redir->token, O_RDWR | O_CREAT, 0777);
	if(check_dir(cmd->redir->token) == 2)
		handle_is_dir_er(menu);
	if(!check_acess_file(cmd->redir->token, 2, menu))
		handle_acess_file_er(menu);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);	
}

void	handle_red_app(t_menu *menu, t_cmds *cmd, int fd_out)
{
	fd_out = open(cmd->redir->token, O_CREAT| O_APPEND | O_RDWR, 0777);
	if(check_dir(cmd->redir->token) == 2)
		handle_is_dir_er(menu);
	if(!check_acess_file(cmd->redir->token, 2, menu))
		handle_acess_file_er(menu);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void handle_red_in(t_menu *menu, t_cmds *cmd, int fd_in)
{
	fd_in = open(cmd->redir->token, O_RDWR , 0777);
	if(check_dir(cmd->redir->token) == 2)
		handle_is_dir_er(menu);
	if(!check_acess_file(cmd->redir->token, 1, menu))
		handle_acess_file_er(menu);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	handle_redirs(t_cmds *cmd, t_menu *menu)
{
	int	fd_out;
	int	fd_in;
	t_args *temp;


	fd_out = STDOUT_FILENO;
	fd_in = STDIN_FILENO;
	temp = cmd->redir;
	while(temp)
	{
		if(cmd->redir->type == RED_OUT)
			handle_red_out(menu, cmd, fd_out);
		else if	(cmd->redir->type == APP_OUT)
			handle_red_app(menu, cmd, fd_out);
		else if (cmd->redir->type == RED_IN)
			handle_red_in(menu, cmd, fd_in);
		else if (cmd->redir->type == HERE_DOC)
		{
			dup2(cmd->here_fds[0], STDIN_FILENO);
			close(cmd->here_fds[0]);
		}
		temp = temp->next;
	}
}

void	process_handler(t_menu *menu)
{
	int	result;
	char *path;
	t_cmds	*first_node;
	t_cmds	*cmds;

	first_node = *(menu->cmds);
	cmds = *(menu->cmds);

	if(create_pid_arr(menu) == 1 && ft_is_built(cmds))
		return (free(menu->pid_arr), menu->pid_arr = NULL, handle_redirs(cmds, menu), handle_builts(cmds, menu));
	if (handle_pipes(&cmds, menu))
		return ;
	handle_redirs(cmds, menu);
	handle_builts(cmds, menu);
	result = 0;
	if(cmds->cmd)
	{
		if(!ft_strncmp(cmds->cmd, "./", 2))
			path = ft_strdup(cmds->cmd);
		else
			path = ft_strjoin("/usr/bin/", cmds->cmd);
		result = execve(path, cmds->args, menu->env);
		free(path);
	}
	if(errno == EACCES)
	{
		result = 126;
	}
	else if(errno == ENOENT)
	{
		if (cmds->cmd && !ft_strncmp(cmds->cmd, "/", 1))
			result = 126;
		else
		{
			write_error_message(" command not found\n");
			result = 127;
		}
	}
	else
		result = 1;
	free_mid_process(menu);
	exit (result);
}