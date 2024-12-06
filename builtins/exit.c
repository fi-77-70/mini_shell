#include "../minishell.h"

int		ft_str_is_nr(char *str)
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
	int					i;
	int						len;

	i = 0;
	while (cmds->args[i])
		i++;
	if (i == 1)
		exit (0);
	if (i > 2)
	{
		write_error_message(" too many arguments\n");
		exit (1);
	}
	i--;
	len = ft_strlen(cmds->args[i]);
	if (!ft_str_is_nr(cmds->args[i]) || len > 20 || (code = ft_atoll(cmds->args[i])) > LLONG_MAX)
	{
		write_error_message(" numeric argument required\n");
		if (cmds == *(menu->cmds))
			exit(2);
		else
			exit(2);
	}
	if (code > 256)
		code = code % 256;
	else if (code < 0)
		while (code < 0)
			code = 256 + code; 
	if (menu->pid_arr)
		free(menu->pid_arr);
	free_all(menu);
	if (menu->is_child == 0)
	{
		free_line(menu->env);
		free(menu);
	}
	exit(code);
}
