/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:03:25 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 16:03:26 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_cmds *cmds, t_menu *menu)
{
	char	*cwd;
	int		arg_nbr;

	arg_nbr = 0;
	while (cmds->args[arg_nbr])
		arg_nbr++;
	if (arg_nbr > 1 && ((ft_strcmp(cmds->args[1], "-") == 0)
			|| (cmds->args[1][0] == '-')))
	{
		write_error_message("Error: no options allowed for pwd\n");
		if (menu->is_child)
			return (free_mid_process(menu), exit(1), 0);
		return (menu->return_code = 1, 1);
	}
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
