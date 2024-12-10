#include "../minishell.h"

int	ft_echo(t_cmds *cmds, t_menu *menu)
{
	int		new_line;
	int		arg_nbr;
	int 	i;
	int		j;

	new_line = 1;
	arg_nbr = 0;
	i = 1;
	j = 1;
	(void)menu;
	while(cmds->args[arg_nbr])
		arg_nbr++;

	if(!arg_nbr)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return(0);
	}
	if (cmds->args[i] && cmds->args[i][0] == '-' && cmds->args[i][1] == 'n')
	{
		while(cmds->args[i][j] == 'n')
			j++;
		if(cmds->args[i][j] == '\0') // se tivermos um arg "-nnnnnnnnnnnn"
		{
			new_line = 0;
			i++;
		}
	}
	while(cmds->args[i])
	{
		ft_putstr_fd(cmds->args[i], STDOUT_FILENO);
		if(cmds->args[i+1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if(new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);

	return(0);
}
