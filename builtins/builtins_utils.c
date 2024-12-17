#include "../minishell.h"

void	handle_builts(t_cmds *cmds, t_menu *menu)
{
	if (!ft_strcmp(cmds->cmd, "echo"))
		ft_echo(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "cd"))
		ft_cd(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "exit"))
		built_exit(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "env"))
		ft_env(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "pwd"))
		ft_pwd(cmds, menu);
	if (!ft_strcmp(cmds->cmd, "export"))
		ft_export(cmds, menu);
/* 	if (!ft_strcmp(cmds->cmd, "unset"))
		ft_unset(cmds, menu);
	if (!menu->is_child)
	{
		ft_putstr_fd("ENTREI\n", menu->fd_out);
		dup2(menu->fd_in, STDIN_FILENO);
		dup2(menu->fd_out, STDOUT_FILENO);
	} */
	return ;
}

char	*ft_strjoin3(const char *s1, char c, const char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 2);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	result[len1] = c;
	ft_memcpy(result + len1 + 1, s2, len2);
	result[len1 + len2 + 1] = '\0';
	return (result);
}

int	ft_strclen_custom(const char *str, char c)
{
	char	*pos;

	if (!str)
		return (0);
	pos = ft_strchr(str, c);
	if (pos)
		return (pos - str);
	return (ft_strlen(str));
}

int	find_env_index(char **env, const char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	if (!env || !key || *key == '\0')
		return (-1);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
