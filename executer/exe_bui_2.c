/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bui_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:19:23 by filferna          #+#    #+#             */
/*   Updated: 2024/12/27 18:32:49 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_menu	*menu(void)
{
	static t_menu	menu;

	return (&menu);
}

void	wem(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(STDERR_FILENO, &str[i++], 1);
}

void	wait_for_process(t_menu *menu)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!menu->pid_arr)
		return ;
	while (menu->pid_arr[i] != 0)
	{
		waitpid(menu->pid_arr[i++], &j, 0);
		if (!WIFEXITED(j))
			menu->return_code = 130;
		else
			menu->return_code = WEXITSTATUS(j);
	}
	free(menu->pid_arr);
	menu->pid_arr = NULL;
}

void	dup_arrr(char **map, t_menu **menu)
{
	t_menu	*temp;
	int		y;

	temp = *menu;
	temp->env = NULL;
	y = 0;
	while (map[y])
		y++;
	temp->env = (char **)malloc(sizeof(char *) * (y + 1));
	y = -1;
	while (map[++y])
	{
		temp->env[y] = ft_strdup(map[y]);
	}
	temp->env[y] = NULL;
}

int	ft_is_built(t_cmds *cmds)
{
	char	*str;

	str = NULL;
	if (cmds->cmd)
		str = cmds->cmd;
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	return (0);
}
