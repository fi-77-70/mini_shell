#include "../minishell.h"

void	create_pid_arr(t_menu *menu)
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
		if(pipe(fds) == -1)
		{
			printf("erro");
			return (1);
		}
		if((menu->pid_arr[i++] = fork()) != 0)
		{
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			cmd = cmd->next;
			close(fds[1]);
			if (!cmd)
				return (dup2(menu->fd_in, STDIN_FILENO), 1);
		}
		else
		{
			*cmds = cmd;
			if(!cmd->next)
				break ;
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
			return (0);
		}
	}
	dup2(menu->fd_out, STDOUT_FILENO);
	close(menu->fd_out);
	return (0);
}

void	handle_redirs(t_cmds *cmd)
{
	int	fd_out;
	int	fd_in;


	fd_out = STDOUT_FILENO;
	fd_in = STDIN_FILENO;
	while(cmd->redir)
	{
		if(cmd->redir->type == RED_OUT)
		{
			fd_out = open(cmd->redir->token, O_RDWR | O_CREAT, 0777);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if	(cmd->redir->type == APP_OUT)
		{
			fd_out = open(cmd->redir->token, O_CREAT| O_APPEND | O_RDWR, 0777);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (cmd->redir->type == RED_IN)
		{

			fd_in = open(cmd->redir->token, O_RDWR , 0777);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		cmd->redir = cmd->redir->next;
	}
}

void	process_handler(t_menu *menu)
{
	int	result;
	int	fd;
	char *path;
	t_cmds	*first_node;
	t_cmds	*cmds;

	fd = 0;
	first_node = *(menu->cmds);
	cmds = *(menu->cmds);
	if(handle_builts(cmds))
		return ;
	create_pid_arr(menu);
	if (handle_pipes(&cmds, menu))
		return ;
	if(cmds->redir)
		handle_redirs(cmds);
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
	if (result == -1)
		printf("ERROR: command not found -- >  [%s]\n", cmds->cmd);
	*(menu->cmds) = first_node;
	free_all(menu);
	if (menu->pid_arr)
		free(menu->pid_arr);
	free_line(menu->env);
	free(menu);
	exit(-1);
}