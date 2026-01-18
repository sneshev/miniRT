/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_info1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:06:17 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/18 19:20:35 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	valid_element(char identifyer, t_element *element)
{
	if (identifyer == 'C')
	{
		if (!element->camera)
			element->camera = true;
		else
			return (false);
	}
	else if (identifyer == 'A')
	{
		if (!element->ambient)
			element->ambient = true;
		else
			return (false);
	}
	else if (identifyer == 'L')
	{
		if (!element->light)
			element->light = true;
		else
			element->light = false;
	}
	return (true);	
}

bool	valid_unit_direction(t_vec3 *dir, char *str)
{
	char	**split;
	float	f[3];

	split = ft_split(str, is_comma);
	if (!split)
		return (false);
	if (arr_count(split) != 3)
		return (free_arr(split), false);
	if (!valid_float(&(f[0]), split[0]))
		return (free_arr(split), false);
	if (!valid_float(&(f[1]), split[1]))
		return (free_arr(split), false);
	if (!valid_float(&(f[2]), split[2]))
		return (free_arr(split), false);
	*dir = (t_vec3){f[0], f[1], f[2]};
	if (length(*dir) != 1.0f)
		return (free_arr(split), false);
	free_arr(split);
	return (true);
}

bool	valid_position(t_vec3 *pos, char *str)
{
	char	**split;
	float	f[3];

	split = ft_split(str, is_comma);
	if (!split)
		return (false);
	if (arr_count(split) != 3)
		return (free_arr(split), false);
	if (!valid_float(&(f[0]), split[0]))
		return (free_arr(split), false);
	if (!valid_float(&(f[1]), split[1]))
		return (free_arr(split), false);
	if (!valid_float(&(f[2]), split[2]))
		return (free_arr(split), false);
	*pos = (t_vec3){f[0], f[1], f[2]};
	free_arr(split);
	return (true);
}

bool	valid_rgb(uint8_t *rgb, char *str)
{
	int	n;
	if (ft_strlen(str) > 3 || !ft_strlen(str))
		return (false);
	n = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		n = n * 10 + (*str - '0');
		str++;
	}
	if (n < 0 || n > 255)
		return (false);
	*rgb = (uint8_t)n;
	return (true);
}

bool	valid_color(t_color *color, char *str)
{
	char	**split;
	t_rgb	rgb;
	
	split = ft_split(str, is_comma);
	if (!split)
		return (false);
	if (arr_count(split) != 3)
		return (free_arr(split), false);
	if (!valid_rgb(&(rgb.r), split[0]))
		return (free_arr(split), false);
	if (!valid_rgb(&(rgb.g), split[1]))
		return (free_arr(split), false);
	if (!valid_rgb(&(rgb.b), split[2]))
		return (free_arr(split), false);
	free_arr(split);
	color->rgb = rgb;
	return (true);
}
