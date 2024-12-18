#include "../minishell.h"

int	ft_unset(t_cmds *cmds, t_menu *menu)
{
	int	i;

	i = 1;
	if(!cmds->args[1])
		return (menu->return_code = 0, 0);

	while (cmds->args[i])
	{
		if (!parse_export_input(cmds->args[i]))
			return (menu->return_code = 1, 1);
		
		i++;
	}
}