/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:03:30 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 16:03:31 by pmachado         ###   ########.fr       */
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
			return (menu->return_code = 1, 1);
		else
			del_variable(menu, cmds->args[i]);
		i++;
	}
	return (0);
}

void	del_variable(t_menu *menu, const char *key)
{
	int	i;
	int	index;

	index = find_env_index(menu->env, key);
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
