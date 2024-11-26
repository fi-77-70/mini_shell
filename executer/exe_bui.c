#include "../minishell.h"

void	wait_for_process(t_menu *menu)
{
	int	i;
	int	*j;

	i = 0;
	j = NULL;
	while(menu->pid_arr[i] != 0)
	{
		printf("wait pid -----> [%d]\n", menu->pid_arr[i]);
		waitpid(menu->pid_arr[i++], j, WUNTRACED);
	}
	free(menu->pid_arr);
	menu->pid_arr = NULL;
}

void dup_arrr(char **map, t_menu **menu)
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

int	pid_get(t_menu *menu)
{
	int	i;
	
	i = fork();
	if (i == 0)
	{
		free_list(menu->mshh);
		free_line(menu->line);
		free_line(menu->env);
		free(menu);
		exit(0);
	}
	else
		return (i);
}