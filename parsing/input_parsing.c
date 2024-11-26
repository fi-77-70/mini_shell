
#include "../minishell.h"

void  ft_unquote_two(t_args **msh, int length)
{
	char *final;
	char quote;
	int i;
	int a;
 	t_args  *temp;

	i = 0;
	a = 0;
	temp = *msh;
	final = (char *)malloc(sizeof(char) * length + 1);
	quote = temp->token[i];
	while (temp->token[i])
	{
    	while (temp->token[i] && temp->token[i] != 39 && temp->token[i] != '"')
    	{
			final[a] = temp->token[i];
			a++;
      		i++;
		}
		quote = temp->token[i];
		i++;
		while (temp->token[i] != quote && temp->token[i])
		{
      		final[a] = temp->token[i];
     		a++;
    		i++;
		}
		if (temp->token[i])
			i++;
	}
	final[a] = 0;
	free((*msh)->token);
	(*msh)->token = final;
}

int ft_unquote(t_args **msh)
{
	char  quote;
	int i;
	int length;
	int n;
	t_args  *temp;

	temp = *msh;
	i = -1;
	n = 0;
	while (temp->token[++i])
	{
		if(temp->token[i] == 39 || temp->token[i] == '"')
		{
			quote = temp->token[i];
			n += 2;
			i++;
			while (temp->token[i] != quote && temp->token[i])
			i++;
			if (temp->token[i] != quote)
				return (0);
		}
	}
	printf("%d\n", n);
	length = ft_strlen(temp->token) - n;
	ft_unquote_two(msh, length);
	return (2);
}

int ft_check_quotes(t_args **mshh)
{
	int zero;
	int check;
	t_args *msh;

	zero = -1;
	check = 1;
	msh = *mshh;
	while (msh)
	{
		while (msh->token[++zero])
		{
			if (msh->token[zero] == '"' || msh->token[zero] == 39)
				check = ft_unquote(&msh);
			if(!check)
				return (0);
			else if (check == 2)
				break ;
		}
		check = 1;
		zero = -1;
		msh = msh->next;
	}
	return (1);
}

int  check_multiple_here_doc(t_args *msh)
{
	int check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == HERE_DOC)
		return (0);
		msh = msh->next;
	}
	return (1);
}

int  check_multiple_app(t_args *msh)
{
	int check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == APP_OUT)
		return (0);
		msh = msh->next;
	}
	return (1);
}

int  check_multiple_red_out(t_args *msh)
{
	int check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == RED_OUT)
		return (0);
		msh = msh->next;
	}
	return (1);
}

int  check_multiple_red_in(t_args *msh)
{
	int check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == RED_IN)
		return (0);
		msh = msh->next;
	}
	return (1);
}

int  check_multiple_pipes(t_args *msh)
{
	int check;

	while (msh->next)
	{
		check = msh->type;
		if (check == msh->next->type && check == PIPE)
		return (0);
		msh = msh->next;
	}
	return (1);
}
int	check_red_file_name(t_args *msh)
{
	int check;

	while (msh->next)
	{
		check = msh->type;
		if ((check == RED_IN || check == RED_OUT || check == APP_OUT || check == HERE_DOC) && msh->next->type != ARG)
			return (0);
		msh = msh->next;
	}
	return (1);
}

int ft_input_check(t_args **mshh)
{
		t_args  *msh;

	msh = *mshh;
	if (!check_multiple_pipes(msh))
		return (0);
	if (!check_multiple_red_in(msh))
		return (0);
	if (!check_multiple_red_out(msh))
		return (0);
	if (!check_multiple_here_doc(msh))
		return (0);
	if (!check_multiple_app(msh))
		return (0);
	if (!check_red_file_name(msh))
		return (0);
	if (!ft_check_quotes(mshh))
		return (0);
	return (1);
  }
