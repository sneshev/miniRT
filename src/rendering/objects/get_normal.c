#include "minirt.h"

bool	is_on_same_plane(t_vec3 *p1, t_vec3 *p2, t_vec3 *normal)
{
	float	d = dot(normalize(*p1 - *p2), normalize(*p1 - *normal));
	if (d < T_MIN && d > -T_MIN)
		return (true);
	return (false);
}

t_vec3	get_cy_normal(t_cylinder *cy, t_vec3 *hitpoint)
{
		t_vec3		p;
		p = cy->center + (cy->unit_dir * (cy->height / 2));
		if (is_on_same_plane(&p, hitpoint, &cy->unit_dir)) {
			return (cy->unit_dir);
		}
		p = cy->center - (cy->unit_dir * (cy->height / 2));
		if (is_on_same_plane(&p, hitpoint, &cy->unit_dir)) {
			return (-cy->unit_dir);
		}
		else
		{
		    t_vec3	cp = *hitpoint - cy->center;
		    float	h = dot(cp, cy->unit_dir);
		    t_vec3	axis_point = cy->center + cy->unit_dir * h;
		    return (normalize(*hitpoint - axis_point));
		}
}

//	doesnt account for hitting back of object yet (needs to flip normal)
t_vec3	get_normal(t_object *object, t_vec3 hitpoint)
{
	t_vec3	normal = (t_vec3){0, 0, 0};

	if (object->type == SPHERE) {
		normal = normalize(hitpoint - ((t_sphere *)object)->center);
	}
	else if (object->type == PLANE)
	{
		normal = ((t_plane *)object)->normal;
	// if (dot(normal, ray.dir) > 0)
	    // normal = normal * -1;
	}
	else if (object->type == CYLINDER)
	{
		normal = get_cy_normal((t_cylinder *)object, &hitpoint);
	}
	return (normal);
}