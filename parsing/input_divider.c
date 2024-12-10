#include "../minishell.h"

char	**get_args(t_args *msh, t_cmds *cmd)
{
	int		i;
	int		size;
	char	**args;
	t_args	*temp;

	i = 0;
	size = 0;
	args = cmd->args;
	temp = msh;
	while (msh)
	{
		if (msh->type == RED_IN || msh->type == HERE_DOC || msh->type == APP_OUT || msh->type == RED_OUT)
			msh = msh->next->next;
		if (msh && msh->type == PIPE)
			break;
		if (msh && msh->type == ARG)
			size++;
		if (msh)
			msh = msh->next;
	}
	if (size == 0)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	while (temp)
	{
		if (temp && temp->type == PIPE)
			break;
		if (temp->type == RED_IN || temp->type == HERE_DOC || temp->type == APP_OUT || temp->type == RED_OUT)
			temp = temp->next;
		if (temp && temp->type == ARG && (!temp->prev || (temp->prev->type != RED_IN && temp->prev->type != RED_OUT && temp->prev->type != APP_OUT && temp->prev->type != HERE_DOC)))
			args[i++] = ft_strdup(temp->token);
		if(temp)
			temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

t_args	*get_redir(t_args *msh)
{
	t_args	*redir;

	redir = (t_args *)malloc(sizeof(t_args));
	redir->type = msh->type;
	if (msh->next)
		redir->token = msh->next->token;
	redir->next = NULL;
	return (redir);
}


void	init_cmds(t_cmds **cmds)
{
	*cmds = (t_cmds *)malloc(sizeof(t_cmds));
	(*cmds)->cmd = NULL;
	(*cmds)->args = NULL;
	(*cmds)->redir = NULL;
	(*cmds)->next = NULL;
}

void	ft_div(t_cmds **cmds, t_args *msh)
{
	t_cmds	*cmd;
	t_args	*redir_begin;
	t_args	*temp;

	cmd = *cmds;
	temp = NULL;
	redir_begin = NULL;
	cmd->args = get_args(msh, cmd);
	if(cmd->args && cmd->args[0] && !cmd->cmd)
		cmd->cmd = ft_strdup(cmd->args[0]);
	while (msh && msh->type != PIPE)
	{
		if (msh->type == RED_IN || msh->type == RED_OUT || msh->type == APP_OUT || msh->type == HERE_DOC)
		{
			if (temp)
			{
				while(temp->next)
					temp = temp->next;
				temp->next = get_redir(msh);
				cmd->redir = temp;
				temp = temp->next;
			}
			else
			{
				temp = get_redir(msh);
				redir_begin = temp;
				cmd->redir = temp;
			}
			msh = msh->next->next;
		}
		else if (msh && msh->type == ARG)
			while (msh && msh->type == ARG)
				msh = msh->next;
	}
		cmd->redir = redir_begin;
}

t_cmds	**ft_cmd_div(t_args *msh)
{
	t_cmds	**cmds;
	t_cmds	*test;
	// t_args	*re_test;
//	int		i;

	cmds = (t_cmds **)malloc(sizeof(t_cmds *));
	*cmds = NULL;
	if (!cmds)
		return (NULL);
	init_cmds(cmds);
	test = *cmds;
	while (msh)
	{
		ft_div(&test, msh);
		while (msh && msh->type != PIPE)
			msh = msh->next;
		if (msh && msh->type == PIPE)
		{
			init_cmds(&test->next);
			test = test->next;
		}
		if(msh)
			msh = msh->next;
	}

	test = *cmds;
/* 	while (test)
	{
		i = 0;
		re_test = test->redir;
		printf("=====================================================\n");
		printf("process cmd: %s\n", test->cmd);
		while (test->args && test->args[i])
			printf("process args: %s\n", test->args[i++]);
		i = 0;
		while (re_test)
		{
			printf("process redir: type-> %d, file-> %s\n", re_test->type, re_test->token);
			re_test = re_test->next;
		}
		printf("=====================================================\n");
		test = test->next;
	} */
	return (cmds);
}
