#include "../minishell.h"

int	ft_cd(t_cmds *cmds, t_menu *menu)
{
	char	*path;
	int		arg_nbr;

	arg_nbr = verify_nbr_args(cmds, menu);
	if (arg_nbr > 2)
		return (1);
	if (arg_nbr == 1 || (cmds->args[1] && cmds->args[1][0] == '~'))
	{
		path = menu->til;
		if (!path)
		{
			ft_putstr_fd("cd: no HOME var \n", STDERR_FILENO);
			menu->return_code = 1;
			return (1);
		}
	}
	else
		path = cmds->args[1];
	change_dir(menu, path);
	return (0);
}

int	verify_nbr_args(t_cmds *cmds, t_menu *menu)
{
	int	arg_nbr;

	arg_nbr = 0;
	while (cmds->args[arg_nbr])
		arg_nbr++;
	if (arg_nbr > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		menu->return_code = 1;
		return (arg_nbr);
	}
	return (arg_nbr);
}

int	change_dir(t_menu *menu, char *path)
{
	char	buffer[1024];
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("cd: Failure obtaining cdw\n", STDERR_FILENO);
		return (menu->return_code = 1, 1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: No such file or directory\n", STDERR_FILENO);
		free(cwd);
		return (menu->return_code = 1, 1);
	}
	update_env_var(menu, "OLDPWD", cwd);
	free(cwd);
	if (getcwd(buffer, 1024) != NULL)
		update_env_var(menu, "PWD", buffer);
	return (menu->return_code = 0, 0);
}

void	update_env_var(t_menu *menu, const char *key, const char *value)
{
	int		i;
	char	*new_var;

	i = 0;
	if (!key || !value)
		return ;
	new_var = ft_strjoin3(key, '=', value);
	if (!new_var)
		return ;
	while (menu->env[i])
	{
		if (ft_strncmp(menu->env[i], key, ft_strlen(key)) == 0
			&& menu->env[i][ft_strlen(key)] == '=')
		{
			free(menu->env[i]);
			menu->env[i] = new_var;
			return ;
		}
		i++;
	}
	menu->env = create_env(menu->env, new_var);
}

char	**create_env(char **env, char *new_var)
{
	int		i;
	int		length;
	char	**new_env;

	i = 0;
	length = 0;
	if (env)
	{
		while (env[length])
			length++;
	}
	new_env = malloc(sizeof(char *) * (length + 2));
	if (!new_env)
		return (NULL);
	while (i < length)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[length] = new_var;
	new_env[length + 1] = NULL;
	if (env)
		free(env);
	return (new_env);
}
