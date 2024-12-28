/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:18:40 by filferna          #+#    #+#             */
/*   Updated: 2024/12/27 17:48:06 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_menu **menu, char **envp)
{
	t_menu	*temp;

	temp = *menu;
	dup_arrr(envp, &temp);
	temp->fd_in = dup(STDIN_FILENO);
	temp->fd_out = dup(STDOUT_FILENO);
	temp->mshh = NULL;
	temp->line = NULL;
	temp->return_code = 0;
	temp->is_child = 0;
	temp->pid_arr = NULL;
	temp->cmds = NULL;
	temp->first_cmd = NULL;
	temp->til = getenv("HOME");
	*menu = temp;
}

int	is_cmd(char *str)
{
	char	*cmd;
	int		result;

	cmd = str;
	result = 0;
	if (!ft_strncmp(cmd, "echo", 4))
		result = 1;
	if (!ft_strncmp(cmd, "cd", 2))
		result = 1;
	if (!ft_strncmp(cmd, "pwd", 3))
		result = 1;
	if (!ft_strncmp(cmd, "export", 6))
		result = 1;
	if (!ft_strncmp(cmd, "unset", 5))
		result = 1;
	if (!ft_strncmp(cmd, "env", 3))
		result = 1;
	if (!ft_strncmp(cmd, "exit", 4))
		result = 1;
	return (result);
}

void	free_line(char **line)
{
	int	j;

	j = -1;
	while (line[++j])
	{
		if (line[j])
			free(line[j]);
		line[j] = NULL;
	}
	free(line);
	line = NULL;
}

int	print_until(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		printf("%c", str[i++]);
	if (str[i] && str[i] == c)
		printf("%c", str[i]);
	return (i);
}
