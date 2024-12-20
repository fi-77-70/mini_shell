/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:03:25 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 18:13:28 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_cmds *cmds, t_menu *menu)
{
	char	*cwd;

	if (cmds->args[1] && ((ft_strcmp(cmds->args[1], "-") == 0)
			|| (cmds->args[1][0] == '-')))
		return (handle_pwd_err(menu, "Error: no options allowed for pwd\n", 1));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = env_get("PWD", menu);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		if (menu->is_child)
			return (free_mid_process(menu), exit(0), 0);
		return (0);
	}
	write_error_message("Issue finding current directory\n");
	if (menu->is_child)
		return (free_mid_process(menu), exit(1), 0);
	return (menu->return_code = 1, 1);
}

int	handle_pwd_err(t_menu *menu, const char *message, int err_code)
{
	write_error_message(message);
	if (menu->is_child)
		return (free_mid_process(menu), exit(0), 0);
	menu->return_code = 1;
	return (err_code);
}
