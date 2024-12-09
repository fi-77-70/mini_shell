#include "../minishell.h"

//#define PATH_MAX	xxxx (pdemos usar a const q esta no header <limits.h>, defini-la manualmente ou alocar dinamicamente)

int	ft_pwd(t_cmds *cmds, t_menu *menu)
{

	char	*cwd;
	int		arg_nbr;

	arg_nbr = 0;
	while(cmds->args[arg_nbr])
		arg_nbr++;
	if(arg_nbr > 1) // se houver algo dps do proprio comando
	{
		if(ft_strcmp(cmds->args[1],"-") == 0) // vemos se estamos a tentar incluir options
		{
			ft_putstr_fd("Error: no options allowed for pwd\n", STDERR_FILENO);
			menu->return_code = 1; //isto conta como general error ou vai haver algum codigo de erro especifico?
			return(1);
		}
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, menu->fd_out);
		ft_putstr_fd("\n", menu->fd_out);
		free(cwd);
		return(0);
	}
	else
	{
		ft_putstr_fd("Issue finding current directory\n", STDERR_FILENO);
		menu->return_code = 1;
		return(1);
	}
}