
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int	count_set(char *str, char *set)
{
	int	i;
	int	x;
	int	ret;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		x = -1;
		while (set[++x])
		{
			if (set[x] == str[i])
			{
				ret++;
				break ;
			}
		}
	}
	printf("ret %d\n", ret);
	return (ret);
}

void	magic_eraser(char *str, char *set, bool f)
{
	char	*ret;
	int		i;
	int		x;

	ret = malloc(sizeof(char) * count_set(str, set) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (*str)
	{
		x = -1;
		while (set[++x])
		{
			if (set[x] == *str && str++)
				x = -1;
		}
		ret[++i] = *str;
	}
	if (f)
		free(str);
	ret[i] = '\0';
	return (ret);
}
