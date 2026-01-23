#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef float	t_vec3 __attribute__ ((vector_size ((sizeof(float) * 4))));

# define X 0
# define Y 1
# define Z 2

#define U 0
#define V 1
#define W 2


float	length(t_vec3 v);
void	normalize(t_vec3 *v);
float	dot(t_vec3 v1, t_vec3 v2);
t_vec3	cross(t_vec3 v1, t_vec3 v2);

#endif