#include "cub3d.h"

/**
 * @todo ft_atoiに数字以外の文字列が渡るとエラーは返さず0になる
 */
int	color_text_to_color_num(char *color_text)
{
	char	**color_text_parts;
	int		color_num;
	int		i;

	if (color_text == NULL)
		end_game(1, "color text is null\n");
	color_text_parts = ft_split(color_text, ',');
	i = 0;
	while (i < 3)
	{
		if (color_text_parts[i] == NULL)
			end_game(1, "invalid color text format\n");
		if (
			ft_atoi(color_text_parts[i]) < 0
			|| ft_atoi(color_text_parts[i]) > 255)
			end_game(1, "color out of range\n");
		i++;
	}
	color_num = ft_atoi(color_text_parts[0]);
	color_num = (color_num << 8) + ft_atoi(color_text_parts[1]);
	color_num = (color_num << 8) + ft_atoi(color_text_parts[2]);
	return (color_num);
}

void	handle_floor(t_info *info, char *color_text)
{
	info->floor_color = color_text_to_color_num(color_text);
}

void	handle_ceiling(t_info *info, char *color_text)
{
	info->ceiling_color = color_text_to_color_num(color_text);
}
