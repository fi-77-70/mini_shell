#include "../minishell.h"

int	handle_builts(t_cmds *cmds)
{
	if (!ft_strcmp(cmds->cmd, "cd"))
		return (ft_change_dir(cmds->args[1]));
	else
		return (0);
}

int	ft_change_dir(const char *path)
{
	DIR	*check;

	if ((check = opendir(path)))
	{
		chdir(path);
		closedir(check);
		return (1);
	}
	else
		return (1);
}