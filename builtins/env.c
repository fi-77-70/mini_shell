/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:03:03 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 16:06:08 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmds *cmds, t_menu *menu)
{
	int	i;

	i = 0;
	if (!menu || !menu->env)
	{
		write_error_message("env: Failed to obtain environment vars\n");
		if (menu->is_child)
			return (free_mid_process(menu), exit(1), 0);
		return (menu->return_code = 1, 1);
	}
	if (cmds->args[1])
	{
		write_error_message("env: Invalid input. No option allowed.\n");
		if (menu->is_child)
			return (free_mid_process(menu), exit(1), 0);
		return (menu->return_code = 1, 1);
	}
	while (menu->env[i])
	{
		if (ft_strchr(menu->env[i], '='))
			printf("%s\n", menu->env[i]);
		i++;
	}
	if (menu->is_child)
		return (free_mid_process(menu), exit(0), 0);
	return (menu->return_code = 0, 0);
}
