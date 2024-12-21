#include "../minishell.h"

void	wem(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(STDERR_FILENO, &str[i++], 1);
}

void	wait_for_process(t_menu *menu)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!menu->pid_arr)
		return ;
	while (menu->pid_arr[i] != 0)
	{
		waitpid(menu->pid_arr[i++], &j, 0);
		menu->return_code = WEXITSTATUS(j);
	}
	free(menu->pid_arr);
	menu->pid_arr = NULL;
}

void	dup_arrr(char **map, t_menu **menu)
{
	t_menu	*temp;
	int		y;

	temp = *menu;
	temp->env = NULL;
	y = 0;
	while (map[y])
		y++;
	temp->env = (char **)malloc(sizeof(char *) * (y + 1));
	y = -1;
	while (map[++y])
	{
		temp->env[y] = ft_strdup(map[y]);
	}
	temp->env[y] = NULL;
}

int	ft_is_built(t_cmds *cmds)
{
	char	*str;

	str = NULL;
	if (cmds->cmd)
		str = cmds->cmd;
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	return (0);
}
