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
