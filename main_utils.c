#include "minishell.h"

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
	if (*mshh)
	{
		free(*mshh);
		*mshh = NULL;
	}
	free(mshh);
	mshh = NULL;
}

void	free_cmds_2(t_cmds *temp)
{
	int		i;
	t_args	*del;

	i = -1;
	if (temp->args)
	{
		while (temp->args[++i])
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
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*temp;

	if (!cmds || !*cmds)
		return ;
	temp = *cmds;
	while (temp)
	{
		if (temp->cmd)
			free(temp->cmd);
		free_cmds_2(temp);
		*cmds = temp->next;
		free(temp);
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

void	handle_sigint(int signum)
{
	(void)signum;
	printf("^C\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
