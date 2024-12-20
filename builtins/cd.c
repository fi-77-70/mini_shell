/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:02:51 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 16:55:43 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmds *cmds, t_menu *menu)
{
	char	*path;
	int		arg_nbr;
	int		alloc;

	path = NULL;
	alloc = 0;
	arg_nbr = verify_nbr_args(cmds, menu);
	if (arg_nbr > 2)
		return (1);
	if (arg_nbr == 1 || (cmds->args[1]
			&& (cmds->args[1][0] == '~' || cmds->args[1][0] == '-')))
	{
		alloc = handle_checks_cd(cmds->args[1], menu, &path);
		if (alloc == -1)
			return (1);
	}
	else
		path = cmds->args[1];
	change_dir(menu, path);
	if (alloc)
		free(path);
	return (0);
}

int	handle_checks_cd(char *arg, t_menu *menu, char **path)
{
	if (arg && arg[0] == '-')
	{
		*path = env_get("OLDPWD", menu);
		return (1);
	}
	*path = menu->til;
	if (!*path)
	{
		ft_putstr_fd("cd: no HOME var \n", STDERR_FILENO);
		menu->return_code = 1;
		return (-1);
	}
	return (0);
}

int	change_dir(t_menu *menu, char *path)
{
	char	buffer[1024];
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = env_get("PWD", menu);
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
