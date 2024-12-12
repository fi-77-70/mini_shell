#include "libft.h"

char	*ft_strjoin_free(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*joined;

	i = 0;
	j = 0;
	while (str1[i])
		i++;
	while (str2[j])
		j++;
	joined = (char *)malloc((i + j + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
	{
		joined[i] = str1[i];
		i++;
	}
	while (str2[j])
		joined[i++] = str2[j++];
	joined[i] = '\0';
	return (free(str1), joined);
}