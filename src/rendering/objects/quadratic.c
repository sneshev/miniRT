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

bool	solve_quadratic(float a, float b, float c, float roots[2])
{
	float	disc;
	float	rev_denom;
	float	sqrt_disc;

	disc = b*b - 4*a*c;
	if (disc > 0)
	{
		sqrt_disc = sqrtf(disc);
		rev_denom = 0.5f / a;
		roots[0] = (-b + sqrt_disc) * rev_denom;
		roots[1] = (-b - sqrt_disc) * rev_denom;
		if (roots[0] > roots[1])
			swapf(&roots[0], &roots[1]);
		return (2);
	}
	else if (disc == 0)
	{
		roots[0] = -0.5f * b / a;
		return (1);
	}
	else
		return (0);
}
