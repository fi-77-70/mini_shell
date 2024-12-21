/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:03:03 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 23:56:05 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmds *cmds, t_menu *menu)
{
	int	i;

	i = 0;
	if (!menu || !menu->env)
	{
		wem("env: Failed to obtain environment vars\n");
		if (menu->is_child)
			return (free_mid_process(menu), exit(1), 0);
		return (menu->return_code = 1, 1);
	}
	if (cmds->args[1])
	{
		wem("env: Invalid input. No option allowed.\n");
		if (menu->is_child)
			return (free_mid_process(menu), exit(1), 0);
		return (menu->return_code = 1, 1);
	}
	while (menu->env[i++])
	{
		if (ft_strchr(menu->env[i], '='))
			printf("%s\n", menu->env[i]);
	}
	if (menu->is_child)
		return (free_mid_process(menu), exit(0), 0);
	return (menu->return_code = 0, 0);
}
