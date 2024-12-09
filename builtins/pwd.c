#include "../minishell.h"

int	ft_pwd(t_cmds *cmds, t_menu *menu)
{
	char	*cwd;
	int		arg_nbr;

	arg_nbr = 0;
	while (cmds->args[arg_nbr])
		arg_nbr++;
	if (arg_nbr > 1)
	{
		if ((ft_strcmp(cmds->args[1], "-") == 0) || (cmds->args[1][0] == '-'))
		{
			ft_putstr_fd("Error: no options allowed for pwd\n", STDERR_FILENO);
			menu->return_code = 1;
			return (1);
		}
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	else
	{
		ft_putstr_fd("Issue finding current directory\n", STDERR_FILENO);
		menu->return_code = 1;
		return (1);
	}
}
