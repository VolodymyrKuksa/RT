#ifndef PARSER_H
# define PARSER_H


# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "rt_types.h"
# define SPHERE_ID 0
# define CONE_ID 1
# define PLANE_ID 2
# define CYLINDER_ID 3
# define SUKA(x, y) ((x > y) ? x : y)

typedef struct	s_parser
{
	int			*num_of_params;

	t_scene		*scene;
	char		**objects;
	char		***params;
	char		**light;
}				t_parser;

void	print_plane(t_obj obj);
void	print_cone(t_obj obj);
void	print_cylinder(t_obj obj);
void	print_sphere(t_obj obj);

#endif
