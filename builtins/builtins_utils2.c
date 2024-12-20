/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:53:23 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 18:13:38 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_nbr_args(t_cmds *cmds, t_menu *menu)
{
	int	arg_nbr;

	arg_nbr = 0;
	while (cmds->args[arg_nbr])
		arg_nbr++;
	if (arg_nbr > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		menu->return_code = 1;
		return (arg_nbr);
	}
	return (arg_nbr);
}

void	print_env(t_menu *menu)
{
	int	i;

	i = 0;
	if (!menu || !menu->env)
	{
		write_error_message("export: Failed to obtain vars\n");
		return ;
	}
	while (menu->env[i])
	{
		printf("declare -x %s\n", menu->env[i]);
		i++;
	}
	menu->return_code = 0;
}

int	key_exists(t_menu *menu, char *key)
{
	int	len;
	int	i;

	i = 0;
	if (!key)
		return (0);
	len = ft_strlen(key);
	while (menu->env[i])
	{
		if (!ft_strncmp(menu->env[i], key, len))
			return (1);
		i++;
	}
	return (0);
}
