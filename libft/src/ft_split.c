/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:54:47 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/18 17:34:43 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, bool (*is_whitespace)(char))
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (is_whitespace(s[i]))
			i++;
		if (s[i])
		{
			j++;
			while (s[i] && !is_whitespace(s[i]))
				i++;
		}
	}
	return (j);
}

static char	**free_array(char **arr, int x)
{
	int	i;

	i = 0;
	while (i <= x)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**split_str(char **arr, char const *s, bool (*is_whitespace)(char))
{
	int	i;
	int	x;
	int	start;

	i = 0;
	x = 0;
	start = 0;
	while (s[i])
	{
		while (is_whitespace(s[i]))
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && !is_whitespace(s[i]))
			i++;
		arr[x] = ft_substr(s, start, i - start);
		if (!arr[x])
			return (free_array(arr, x));
		x++;
	}
	arr[x] = NULL;
	return (arr);
}

char	**ft_split(const char *s, bool (*is_whitespace)(char))
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (word_count(s, is_whitespace) + 1));
	if (!arr)
		return (NULL);
	return (split_str(arr, s, is_whitespace));
}

// int	main(void)
// {
// 	const char	*s = "hello 	how	are.   you 	\n";
// 	char		**result = split(s, is_whitespace);
// 	int			i;

// 	if (!result)
// 		return (1);
// 	i = 0;
// 	printf("%s\n", s);
// 	while (result[i])
// 	{
// 		printf("result[%d]: %s\n", i, result[i]);
// 		i++;
// 	}
// 	free_array(result, i);
// }
