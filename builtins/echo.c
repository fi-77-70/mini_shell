/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:02:59 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 16:03:00 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_cmds *cmds, t_menu *menu)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	(void)menu;
	i = check_n_opt(cmds, &new_line);
	while (cmds->args[i])
	{
		printf("%s", cmds->args[i]);
		if (cmds->args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	if (menu->is_child)
	{
		free_mid_process(menu);
		exit(0);
	}
	return (0);
}

int	check_n_opt(t_cmds *cmds, int *new_line)
{
	int	i;
	int	j;

	i = 1;
	*new_line = 1;
	while (cmds->args[i])
	{
		j = 1;
		if (cmds->args[i] && cmds->args[i][0] == '-' && cmds->args[i][1] == 'n')
		{
			while (cmds->args[i][j] == 'n')
				j++;
			if (cmds->args[i][j] == '\0')
			{
				*new_line = 0;
				i++;
				continue ;
			}
		}
		break ;
	}
	return (i);
}
