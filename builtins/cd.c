#include "../minishell.h"

void	handle_builts(t_cmds *cmds, t_menu *menu)
{
/* 	if (!ft_strcmp(cmds->cmd, "echo"))
		ft_echo(cmds, menu); */
	if (!ft_strcmp(cmds->cmd, "cd"))
		ft_change_dir(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "exit"))
		built_exit(cmds, menu);
/* 	if (!ft_strcmp(cmds->cmd, "export"))
		ft_export(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "unset"))
		ft_unset(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "env"))
		ft_env(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "pwd"))
		ft_pwd(cmds, menu); */
	return ;
}

int	ft_change_dir(t_cmds *cmds, t_menu *menu)
{
	DIR	*check;
	char **path;
	int	i;
	int	a;

	path = NULL;
	if (cmds->args)
		path = cmds->args;
	i = 1;
	a = -1;
	while (cmds->args[++a])
		;
	if (a > 2)
		return (write_error_message(" too many arguments\n"), menu->return_code = 1, 1);
	if ((check = opendir(cmds->args[i])))
	{
		chdir(cmds->args[i]);
		closedir(check);
		return (1);
	}
	else
		return (menu->return_code = 1, 1);
}