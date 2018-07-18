#ifndef PARSER_H
# define PARSER_H


# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "json.h"
# include "rt_types.h"
# define SPHERE_ID 0
# define CONE_ID 1
# define PLANE_ID 2
# define CYLINDER_ID 3
# define SUKA(x, y) ((x > y) ? x : y)

void	        print_plane(t_obj obj);
void	        print_cone(t_obj obj);
void	        print_cylinder(t_obj obj);
void	        print_sphere(t_obj obj);
t_obj			default_sphere(void);
char		    *read_file(int fd, size_t *size);
t_obj			default_cone(void);
t_obj			default_cylinder(void);
t_obj			default_plane(void);

void			camera_default(t_cam *cam);
void			check_camera(t_cam *cam);
void			get_cam_params2(char *name, json_value v, t_scene *scene);
void			get_camera_params(json_value *value, t_scene *scene);
void			fillthescene(json_value *value, t_scene *scene);


void			error_fedun(char *er);
void			minus_camera(cl_float3 *pos, cl_float3 cam_pos);
void			fill_position(char *name, cl_float value, cl_float3 *pos);
void			fill_color(char *name, cl_float value, t_obj *tmp);
void			init_rotate(t_basis *basis, cl_float3 rot);
void			checksumandemiss(t_obj *tmp);
void			parselight(json_value *value, t_obj *tmp);
void			fill_common(char *name, t_obj *tmp, json_value *v, cl_float3 *rot);
void			fillthecylind(json_value *value, t_scene *scene);
void			fillthecone(json_value *value, t_scene *scene);
void			filltheplane(json_value *value, t_scene *scene);
void			fillthesphere(json_value *value, t_scene *scene);
void			parse_scene(int argc, char **argv, char **contents, size_t *len);
#endif
