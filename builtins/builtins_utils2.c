/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:53:23 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/21 16:40:50 by filferna         ###   ########.fr       */
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

int	key_exists(t_menu *menu, char *key)
{
	int	len;
	int	i;

	i = 0;
	if (!key)
		return (0);
	len = ft_strlen(key);
	if (ft_strchr(key, '+'))
		len--;
	while (menu->env[i])
	{
		if (!ft_strncmp(menu->env[i], key, len))
			return (1);
		i++;
	}
	return (0);
}

void	print_env(t_menu *menu)
{
	int		i;
	int		a;
	char	**print_alpha;

	i = 0;
	if (!menu || !menu->env)
		return (wem("export: Failed to obtain vars\n"));
	print_alpha = dup_rrr(menu->env);
	if (!print_alpha)
		return ;
	sort_alpha(print_alpha);
	while (print_alpha[i])
	{
		printf("declare -x ");
		if (ft_strchr(print_alpha[i], '='))
			a = print_until(print_alpha[i], '=') + 1;
		else
			a = 0;
		if (ft_strchr(print_alpha[i], '='))
			printf("\"%s\"\n", print_alpha[i++] + a);
		else
			printf("%s\n", print_alpha[i++] + a);
	}
	free_line(print_alpha);
	menu->return_code = 0;
}

char	**dup_rrr(char **map)
{
	char	**dup;
	int		y;

	dup = NULL;
	y = 0;
	while (map[y])
		y++;
	dup = (char **)malloc(sizeof(char *) * (y + 1));
	y = -1;
	while (map[++y])
	{
		dup[y] = ft_strdup(map[y]);
	}
	dup[y] = NULL;
	return (dup);
}

void	sort_alpha(char **array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
