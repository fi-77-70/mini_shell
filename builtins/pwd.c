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
			write_error_message("Error: no options allowed for pwd\n");
			menu->return_code = 1;
			return (1);
		}
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s", cwd);
		printf("\n");
		free(cwd);
		return (0);
	}
	else
	{
		write_error_message("Issue finding current directory\n");
		menu->return_code = 1;
		return (1);
	}
}
