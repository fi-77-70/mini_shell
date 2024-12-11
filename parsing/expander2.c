#include "../minishell.h"

char	*ft_expand(char *line, t_menu *menu)
{
	int i;
	int quote;

	i = 0;
	quote = -1;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '"')
			quote *= -1;
		if (line[i] == 39 && quote < 0)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
		}
		if (line[i] && line[i + 1] && line[i] == '$' && (ft_isalnum(line[i + 1])
				|| line[i + 1] == '?'))
			line = ft_expander(line, i, menu);
		if (line[i] == 92 && line[i + 1])
			i++;
		if (line[i])
			i++;
	}
	return (line);
}