/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:20:01 by filferna          #+#    #+#             */
/*   Updated: 2024/12/28 21:05:28 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_acess_file_er(t_menu *menu)
{
	wem(" Permission denied\n");
	if (menu->is_child)
	{
		free_mid_process(menu);
		exit(1);
	}
	return (menu->return_code = 1, 1);
}

int	handle_red_out(t_menu *menu, t_args *temp, int fd_out)
{
	fd_out = open(temp->token, O_RDWR | O_CREAT | O_TRUNC, 0777);
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
		if (temp->type == RED_OUT && handle_red_out(menu, temp, fd_out))
			return (1);
		else if (temp->type == APP_OUT && handle_red_app(menu, temp, fd_out))
			return (1);
		else if (temp->type == RED_IN && handle_red_in(menu, temp, fd_in))
			return (1);
		else if (temp->type == HERE_DOC)
		{
			dup2(cmd->here_fds[0], STDIN_FILENO);
			close(cmd->here_fds[0]);
		}
		temp = temp->next;
	}
	return (0);
}
