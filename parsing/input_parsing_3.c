#include "../minishell.h"

int	check_red_file_name(t_args *msh)
{
	int	check;

	while (msh)
	{
		check = msh->type;
		if ((check == RED_IN || check == RED_OUT || check == APP_OUT
				|| check == HERE_DOC) && (!msh->next || msh->next->type != ARG))
			return (0);
		msh = msh->next;
	}
	return (1);
}
