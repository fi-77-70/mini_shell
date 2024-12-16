#include "../minishell.h"

int	ft_env(t_menu *menu)
{
	int		i;

	i = 0;
	if(!menu->env)
	{
		ft_putstr_fd("env: Failure obtaining environment vars\n", STDERR_FILENO);
		return (menu->return_code = 1, 1);
	}
	while(menu->env[i])
	{
		ft_putstr_fd(menu->env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}