/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:43:32 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/17 16:45:11 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 42

typedef enum e_status
{
	GNL_OK,
	GNL_EOF,
	GNL_ERROR
}			t_status;

t_status	get_next_line(char **line, int fd);
t_status	exit_status(char **ptr, t_status status);
int			find_newline(const char *str);

