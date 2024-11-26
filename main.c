#include "minishell.h"

int	is_cmd(char *str)
{
	char	*cmd;
	int		result;

	cmd = str;
	result = 0;
	if(!strncmp(cmd, "echo", 4))
		result = 1;
	if(!strncmp(cmd, "cd", 2))
		result = 1;
	if(!strncmp(cmd, "pwd", 3))
		result = 1;
	if(!strncmp(cmd, "export", 6))
		result = 1;
	if(!strncmp(cmd, "unset", 5))
		result = 1;
	if(!strncmp(cmd, "env", 3))
		result = 1;
	if(!strncmp(cmd, "exit", 4))
		result = 1;
	return (result);
}
void	free_line(char **line)
{
	int	j;
	
	j = -1;
	while(line[++j])
	{
		if (line[j])
			free(line[j]);
		line[j] = NULL;
	}
	free(line);
	line = NULL;
}

void	free_list(t_args **mshh)
{
	t_args	*temp;

	if (!mshh)
		return ;
	while (*mshh)
	{
		temp = (*mshh)->next;
		if ((*mshh)->token)
		{
			free((*mshh)->token);
			(*mshh)->token = NULL;
		}
		free(*mshh);
		*mshh = NULL;
		*mshh = temp;
	}
	if(*mshh)
	{
		free(*mshh);
		*mshh = NULL;
	}
	free(mshh);
	mshh = NULL;
}

void	init_struct(t_menu **menu, char **envp)
{
	t_menu *temp;

	temp = *menu;
	temp = (t_menu *)malloc(sizeof(t_menu));
	dup_arrr(envp, &temp);
	temp->fd_in = dup(STDIN_FILENO);
	temp->fd_out = dup(STDOUT_FILENO);
	temp->mshh = NULL;
	temp->pid_arr = NULL;
	temp->cmds = NULL;
	temp->til = getenv("HOME");
	*menu = temp;
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*temp;
	t_args	*del;
	int		i;

	if (!cmds || !*cmds)
		return ;
	temp = *cmds;
	while(temp)
	{
		i = -1;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->args)
		{
			while(temp->args[++i])
				free(temp->args[i]);
			free(temp->args);
		}
		if (temp->redir)
		{
			while (temp->redir)
			{
				del = temp->redir->next;
				free(temp->redir);
				temp->redir = del;
			}
		}
		*cmds = temp->next;
		free (temp);
		temp = NULL;
		temp = *cmds;
	}
	free(cmds);
	cmds = NULL;
}

void	free_all(t_menu *menu)
{
	free_list(menu->mshh);
	free_cmds(menu->cmds);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_menu	*menu;
	t_args	*msh;
	t_args	*temp;
	(void)ac;
	(void)av;

	msh = NULL;
	menu = NULL;
	init_struct(&menu, envp);
	while(1)
	{
		str = readline("minishell: ");
		if(!str)
			return (printf("exit\n"),free_line(menu->env), free(menu), 0);
		add_history(str);
		menu->mshh = (t_args **)malloc(sizeof(t_args *));
		*(menu->mshh) = msh;
		menu->line = ft_splot(str);
		if (!menu->line[0])
		{
			free(menu->mshh);
			free(menu->line);
			continue;
		}
		msh = lexer(menu->mshh, menu->line, menu);
		free_line(menu->line);
		*(menu->mshh) = msh;
		expand(menu->mshh, menu);
		temp = msh;
		if (ft_input_check(menu->mshh))
		{
			while (temp)
			{
				printf("token --> [%s]\n", temp->token);
				printf("type  --> [%d]\n", temp->type);
				temp = temp->next;
			}
			menu->cmds = ft_cmd_div(msh);
			process_handler(menu);
			if(menu->pid_arr)
				wait_for_process(menu);
		}
		else
			printf("ERROR IN PARSING\n");
		if(!menu->cmds)
			menu->cmds = ft_cmd_div(msh);
		*(menu->mshh) = msh;
		free_all(menu);
	}
}
