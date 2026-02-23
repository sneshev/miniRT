#include "minirt.h"

static void	swapf(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	solve_quadratic_ez(float b, float c, float t[2])
{
	float	disc;
	float	sqrt_disc;

	disc = b*b - c;
	if (disc > 0.0f)
	{
		sqrt_disc = sqrtf(disc);
		t[0] = -b - sqrt_disc;
		t[1] = -b + sqrt_disc;
		if (t[0] > t[1])
			swapf(&t[0], &t[1]);
		return (2);
	}
	else if (disc == 0)
	{
		t[0] = -b;
		t[1] = -1;
		return (1);
	}
	else
	{
		t[0] = -1;
		t[1] = -1;
		return (0);
	}
}
