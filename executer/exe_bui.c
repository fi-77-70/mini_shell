#include "../minishell.h"

void	free_mid_process(t_menu *menu)
{
	menu->cmds = menu->first_cmd;
	free_all(menu);
	if (menu->pid_arr)
		free(menu->pid_arr);
	free_line(menu->env);
	free(menu);
}

int	check_acess_file(char *str, int per, t_menu *menu)
{
	if (access(str, F_OK))
		return (write_error_message(" No such file or directory\n"),
			free_mid_process(menu), exit(1), 1);
	if (per == 1 && access(str, R_OK))
		return (write_error_message(" Permission denied\n"),
			free_mid_process(menu), exit(1), 1);
	if (per == 2 && access(str, W_OK))
		return (write_error_message(" Permission denied\n"),
			free_mid_process(menu), exit(1), 1);
	if (per == 3 && access(str, X_OK))
		return (write_error_message(" Permission denied\n"),
			free_mid_process(menu), exit(1), 1);
	else
		return (1);
}

int	check_dir(char *str)
{
	struct stat	buffer;

	if (stat(str, &buffer) == -1)
	{
		perror("stat");
		return (1);
	}
	else if (S_ISDIR(buffer.st_mode))
		return (2);
	else if (S_ISREG(buffer.st_mode))
		return (0);
	else
		return (1);
}

int	is_white_space(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}

void	write_error_message(char *str)
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
		// printf("wait pid -----> [%d]\n", menu->pid_arr[i]);
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

int	ft_is_built(t_cmds *cmds)
{
	char	*str;

	str = NULL;
	if (cmds->cmd)
		str = cmds->cmd;
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	/* 	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1); */
	return (0);
}
