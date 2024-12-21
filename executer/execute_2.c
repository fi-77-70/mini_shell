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

int	p_u_c(t_menu *menu, t_cmds *cmd, int *fds, t_cmds **cmds)
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
		menu->pid_arr[i] = fork();
		if (menu->pid_arr[i++] != 0)
		{
			pipe_utils_parent(fds);
			cmd = cmd->next;
			if (!cmd)
				return (dup2(menu->fd_in, STDIN_FILENO), close(fds[1]), 1);
		}
		else
			return (p_u_c(menu, cmd, fds, cmds));
	}
	return (0);
}

int	handle_is_dir_er(t_menu *menu)
{
	wem("Is a directory\n");
	if (menu->is_child)
	{
		free_mid_process(menu);
		exit(127);
	}
	return (menu->return_code = 127, 1);
}
