/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:03:08 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 20:09:40 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_is_nr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[0] == '-' || str[i] == '+')
			i++;
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

void	built_exit(t_cmds *cmds, t_menu *menu)
{
	long long	code;
	int			i;
	int			len;
	char		*itoa;

	i = 0;
	while (cmds->args[i])
		i++;
	if (i == 1)
		exit(0);
	if (i > 2)
		return (handle_too_many_args(menu));
	i--;
	len = ft_strlen(cmds->args[i]);
	if (*(cmds->args[i]) == '+')
		len--;
	code = ft_atoll(cmds->args[i]);
	itoa = ft_itol(code);
	if (!ft_str_is_nr(cmds->args[i]) || len > 20
		|| (size_t)len != ft_strlen(itoa))
		handle_invalid_arg(menu, itoa);
	free(itoa);
	free_mid_process(menu);
	exit(code % 256);
}

void	handle_too_many_args(t_menu *menu)
{
	write_error_message("exit: too many arguments\n");
	if (menu->is_child)
	{
		free_mid_process(menu);
		exit(1);
	}
	else
		menu->return_code = 1;
}

void	handle_invalid_arg(t_menu *menu, char *itoa)
{
	free(itoa);
	write_error_message("exit: numeric argument required\n");
	free_mid_process(menu);
	exit(2);
}
