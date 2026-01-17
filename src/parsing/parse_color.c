/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:47:43 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/15 20:48:08 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	to_pos_int(char *s)
{
	int	i;
	int	nbr;

	if (!s)
		return (-1);
	i = 0;
	nbr = 0;
	while (s[i])
	{
		nbr = nbr + (s[i] - '0');
		if (s[i + 1] != '\0')
			nbr = nbr * 10;
		i++;
	}
	return (nbr);
}

bool	to_rgb_value(int *v, char *str)
{

	if (ft_strlen(str) > 4)
		return (printf("invalid color length\n"), false);
	*v = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (printf("invalid color char\n"), false);
		*v += (*str - '0');
		str++;
		if (*str)
			*v *= 10;
	}
	if (*v < 0 || *v > 255)
		return (printf("invalid color\n"), false);
	return (true);
}

bool	to_color(t_color *color, char *str)
{
	char	**split;
	
	split = ft_split(str, ',');
	if (!split)
		return (printf("split error\n"), false);
	if (arr_count(split) != 3)
		return (printf("invalid color arr count\n"), false);
	if (!to_rgb_value(&(color->r), split[0]))
		return (printf("invalid color r\n"), false);
	printf("color r: %d\n", color->r);
	if (!to_rgb_value(&(color->g), split[1]))
		return (printf("invalid color g\n"), false);
	printf("color g: %d\n", color->g);
	if (!to_rgb_value(&(color->b), split[2]))
		return (printf("invalid color b\n"), false);
	printf("color b: %d\n", color->b);
	return (true);
}
