#include "../minishell.h"

int	handle_builts(t_cmds *cmds, t_menu *menu)
{
	if (!ft_strcmp(cmds->cmd, "cd"))
		return (ft_change_dir(cmds->args, menu));
	else if (!ft_strcmp(cmds->cmd, "exit"))
		return (built_exit(cmds, menu), 1);
	else
		return (0);
}

int	ft_change_dir(char **path, t_menu *menu)
{
	DIR	*check;
	int	i;

	i = 0;
	while (path[i++])
		;
	if (i != 2)
		return (write_error_message(" too many arguments\n"), menu->return_code = 1, 1);
	i--;
	if ((check = opendir(path[i])))
	{
		chdir(path[i]);
		closedir(check);
		return (1);
	}
	else
		return (menu->return_code = 1, 1);
}