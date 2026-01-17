/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:43:32 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/17 18:09:52 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFFER_SIZE 42

// We changed our get next line to return a exit status,
// passing the line as an address to be filled.
// if we reach end of file we will return GNL_EOF and the
// last line (wether it holds data or is empty) instead of
// NULL.

typedef enum e_status
{
	GNL_OK,
	GNL_EOF,
	GNL_ERROR
}			t_status;

t_status	get_next_line(char **line, int fd);
t_status	exit_status(char **ptr, t_status status);
int			find_newline(const char *str);

#endif
