/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:03:30 by pmachado          #+#    #+#             */
/*   Updated: 2025/01/03 11:11:21 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_cmds *cmds, t_menu *menu)
{
	int	i;

	i = 1;
	if (!cmds->args[1])
		return (menu->return_code = 0, 0);
	while (cmds->args[i])
	{
		if (!parse_export_input(cmds->args[i]))
		{
			if (menu->is_child)
				return (free_mid_process(menu), exit(0), 0);
			return (menu->return_code = 0, 1);
		}
		else
			del_variable(menu, cmds->args[i]);
		i++;
	}
	if (menu->is_child)
		return (free_mid_process(menu), exit(0), 0);
	return (0);
}

void	del_variable(t_menu *menu, const char *key)
{
	int	i;
	int	index;

	index = find_env_index(menu->env, key, 1);
	if (index == -1)
		return ;
	free(menu->env[index]);
	i = index;
	while (menu->env[i + 1])
	{
		menu->env[i] = menu->env[i + 1];
		i++;
	}
	menu->env[i] = NULL;
}
