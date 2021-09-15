#include "cub3d.h"

int	comma_cnt(char *color_text)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (color_text[i])
	{
		if (color_text[i] == ',')
			cnt++;
		i++;
	}
	return (cnt);
}

void	check_color(t_info *info, char **color_text_parts)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		if (color_text_parts[i] == NULL)
			end_game(info, 1, "ERROR: Invalid color text format.\n");
		if (
			ft_atoi(color_text_parts[i]) < 0
			|| ft_atoi(color_text_parts[i]) > 255)
			end_game(info, 1, "ERROR: Color out of range.\n");
		j = 0;
		while (color_text_parts[i][j])
		{
			if (!ft_isdigit(color_text_parts[i][j]))
				end_game(info, 1, "ERROR: Invalid color code.\n");
			j++;
		}
		i++;
	}
	if (color_text_parts[3] != NULL)
		end_game(info, 1, "ERROR: Too much color element.\n");
}

int	color_text_to_color_num(t_info *info, char *color_text)
{
	char	**color_text_parts;
	int		color_num;

	if (color_text == NULL)
		end_game(info, 1, "ERROR: Color text is null.\n");
	if (comma_cnt(color_text) > 2)
		end_game(info, 1, "ERROR: Too much comma.\n");
	color_text_parts = ft_split(color_text, ',');
	check_color(info, color_text_parts);
	color_num = ft_atoi(color_text_parts[0]);
	color_num = (color_num << 8) + ft_atoi(color_text_parts[1]);
	color_num = (color_num << 8) + ft_atoi(color_text_parts[2]);
	free_parts(color_text_parts);
	return (color_num);
}

void	handle_floor(t_info *info, char **color_text)
{
	info->floor_color = color_text_to_color_num(info, color_text[1]);
	free_parts(color_text);
}

void	handle_ceiling(t_info *info, char **color_text)
{
	info->ceiling_color = color_text_to_color_num(info, color_text[1]);
	free_parts(color_text);
}
