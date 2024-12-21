/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:19:36 by filferna          #+#    #+#             */
/*   Updated: 2024/12/21 15:38:51 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_3(t_menu *menu, t_cmds *cmds, int *result)
{
	char	*path;

	if (!ft_strncmp(cmds->cmd, "/", 1) || !ft_strncmp(cmds->cmd, "./", 2))
		path = ft_strdup(cmds->cmd);
	else
		path = get_command_path(cmds, menu);
	*result = execve(path, cmds->args, menu->env);
	free(path);
}

int	error_exe(t_cmds *cmds)
{
	if (check_dir(cmds->cmd) == 2)
	{
		wem(cmds->cmd);
		wem(": Is a directory\n");
		return (126);
	}
	else
	{
		wem(cmds->cmd);
		wem(": Permission denied\n");
		return (126);
	}
}

int	error_exe2(t_cmds *cmds)
{
	if (!ft_strncmp(cmds->cmd, "/", 1) || !ft_strncmp(cmds->cmd, "./", 2))
	{
		if (check_dir(cmds->cmd) == 2)
		{
			wem(cmds->cmd);
			wem(": Is a directory\n");
			return (126);
		}
		else
		{
			wem(cmds->cmd);
			wem(": No such file or directory\n");
			return (127);
		}
	}
	return (0);
}

void	exe_2(t_menu *menu, t_cmds *cmds)
{
	int	result;

	result = 0;
	if (cmds->cmd)
		exe_3(menu, cmds, &result);
	if (errno == EACCES)
		result = error_exe(cmds);
	else if (errno == ENOENT)
		result = error_exe2(cmds);
	else
		result = 1;
	free_mid_process(menu);
	exit(result);
}

void	process_handler(t_menu *menu)
{
	t_cmds	*cmds;

	cmds = *(menu->cmds);
	if (create_pid_arr(menu) == 1 && ft_is_built(cmds))
		return (free(menu->pid_arr), menu->pid_arr = NULL, handle_builts(cmds,
				menu), reset_ouput(menu));
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
