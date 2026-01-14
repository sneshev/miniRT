/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:33:28 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/14 16:33:50 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*newstring;

	if (!s1 || !(*s1))
		return ((char *)s2);
	if (!s2 || !(*s2))
		return ((char *)s1);
	newstring = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstring == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		newstring[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		newstring[i] = *s2;
		s2++;
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
