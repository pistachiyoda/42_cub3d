#include "cub3d.h"

void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i] != NULL)
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}
