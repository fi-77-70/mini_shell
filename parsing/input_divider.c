#include "../minishell.h"

void	init_cmds(t_cmds **cmds)
{
	*cmds = (t_cmds *)malloc(sizeof(t_cmds));
	(*cmds)->cmd = NULL;
	(*cmds)->args = NULL;
	(*cmds)->redir = NULL;
	(*cmds)->next = NULL;
}

void	ft_div_2(t_cmds **cmds, t_args *msh, t_args **rb, t_args **tem)
{
	t_args	*temp;

	temp = *tem;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = get_redir(msh);
		(*cmds)->redir = temp;
		temp = temp->next;
	}
	else
	{
		temp = get_redir(msh);
		*rb = temp;
		(*cmds)->redir = temp;
	}
	*tem = *rb;
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
	if (cmd->args && cmd->args[0] && !cmd->cmd)
		cmd->cmd = ft_strdup(cmd->args[0]);
	while (msh && msh->type != PIPE)
	{
		if (msh->type == RED_IN || msh->type == RED_OUT || msh->type == APP_OUT
			|| msh->type == HERE_DOC)
		{
			ft_div_2(&cmd, msh, &redir_begin, &temp);
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
		if (msh)
			msh = msh->next;
	}
	test = *cmds;
	return (cmds);
}
