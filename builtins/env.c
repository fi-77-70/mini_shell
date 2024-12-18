#include "../minishell.h"

int	ft_env(t_cmds *cmds, t_menu *menu)
{
	int	i;

	i = 0;
	if (!menu || !menu->env)
	{
		ft_putstr_fd("env: Failed to obtain environment vars\n", STDERR_FILENO);
		return (menu->return_code = 1, 1);
	}
	if (cmds->args[1])
	{
		ft_putstr_fd("env: Invalid input. No option allowed.\n", STDERR_FILENO);
		return (menu->return_code = 1, 1);
	}
	while (menu->env[i])
	{
		if (ft_strchr(menu->env[i], '='))
		{
			ft_putstr_fd(menu->env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (menu->return_code = 0, 0);
}

// precisamos de checkar os processos pq com pipes o comando executa duas vezes.