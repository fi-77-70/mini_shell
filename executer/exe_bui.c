/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:18:52 by filferna          #+#    #+#             */
/*   Updated: 2024/12/27 17:49:15 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mid_process(t_menu *menu)
{
	menu->cmds = menu->first_cmd;
	free_all(menu);
	if (menu->pid_arr)
		free(menu->pid_arr);
	free_line(menu->env);
}

int	check_acess_file_2(char *str, int per, t_menu *menu)
{
	if (per == 2 && access(str, W_OK))
	{
		if (!menu->is_child)
			return (wem(" Permission denied\n"), menu->return_code = 1, 0);
		return (wem(" Permission denied\n"),
			free_mid_process(menu), exit(1), 0);
	}
	if (per == 3 && access(str, X_OK))
	{
		if (!menu->is_child)
			return (wem(" Permission denied\n"), menu->return_code = 1, 0);
		return (wem(" Permission denied\n"),
			free_mid_process(menu), exit(1), 1);
	}
	return (3);
}

int	check_acess_file(char *str, int per, t_menu *menu)
{
	int	res;

	if (access(str, F_OK))
	{
		if (!menu->is_child)
			return (wem(" No such file or directory\n"),
				menu->return_code = 1, 0);
		return (wem(" No such file or directory\n"),
			free_mid_process(menu), exit(1), 0);
	}
	if (per == 1 && access(str, R_OK))
	{
		if (!menu->is_child)
			return (wem(" Permission denied\n"), menu->return_code = 1, 0);
		return (wem(" Permission denied\n"),
			free_mid_process(menu), exit(1), 0);
	}
	res = check_acess_file_2(str, per, menu);
	if (res != 3)
		return (0);
	else
		return (1);
}

int	check_dir(char *str)
{
	struct stat	buffer;

	if (stat(str, &buffer) == -1)
		return (1);
	else if (S_ISDIR(buffer.st_mode))
		return (2);
	else if (S_ISREG(buffer.st_mode))
		return (0);
	else
		return (1);
}

int	is_white_space(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}
