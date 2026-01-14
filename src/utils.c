#include "stdbool.h"

bool	is_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

bool	is_newline(char c)
{
	if (c == '\n')
		return (true);
	return (false);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\v' || c == '\t')
		return (true);
	return (false);

}

bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (is_whitespace(*line) == false)
			return (false);
		line++;
	}
	return (true);
}
