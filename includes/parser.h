/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:43:19 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/25 10:43:22 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void            print_scene(t_scene *scene);
void	        print_plane(t_obj obj);
void	        print_cone(t_obj obj);
void	        print_cylinder(t_obj obj);
void	        print_sphere(t_obj obj);
void			print_torus(t_obj obj);
void			print_rectangle(t_obj obj);
void			print_disk(t_obj obj);
void			print_ellipse(t_obj obj);
void			print_triangle(t_obj obj);
void			print_parallelogram(t_obj obj);


t_obj			default_parallelogram(void);
t_obj			default_sphere(void);
char		    *read_file(int fd, size_t *size);
t_obj			default_cone(void);
t_obj			default_cylinder(void);
t_obj			default_plane(void);
t_obj			default_torus(void);
t_obj           default_rectangle(void);
t_obj			default_disk(void);
t_obj			default_ellipse(void);
t_obj			default_triangle(void);

void			camera_default(t_cam *cam);
void			check_camera(t_cam *cam);
void			get_cam_params2(char *name, json_value v, t_scene *scene);
void			get_camera_params(json_value *value, t_scene *scene);
void			fillthescene(json_value *value, t_scene *scene);


void			ftoa(float flt, int after_point, int xy, int fd);
void			error_fedun(char *er);
void			minus_camera(cl_float3 *pos, cl_float3 cam_pos, int znak);
void			fill_position(char *name, cl_float value, cl_float3 *pos);
void			fill_color(char *name, cl_float value, t_obj *tmp);
void			init_rotate(t_basis *basis, cl_float3 rot);
void			checksumandemiss(t_obj *tmp);
void			parselight(json_value *value, t_obj *tmp);

void			fill_ellipse_centers(char *name, json_value v, t_obj *tmp);
void			fill_triangle_points(char *name, json_value v, t_obj *tmp);
void			fill_cone_params(char *name, json_value v, t_obj *tmp);
void			fill_cylinder_params(char *name, json_value v, t_obj *tmp);
void			fill_common(char *name, t_obj *tmp, json_value *v, cl_float3 *rot);
void			fillthecylind(json_value *value, t_scene *scene);
void			fillthecone(json_value *value, t_scene *scene);
void			filltheplane(json_value *value, t_scene *scene);
void			fillthesphere(json_value *value, t_scene *scene);
void			filltorus(json_value *value, t_scene *scene);
void			fillrectangle(json_value *value, t_scene *scene);
void			filldisk(json_value *value, t_scene *scene);
void			fillellipse(json_value *value, t_scene *scene);
void			filltriangle(json_value *value, t_scene *scene);
void			fillparallelogram(json_value *value, t_scene *scene);


void			parse_scene(int argc, char **argv, char **contents, size_t *len);

int				parse_server_data(int ac, char **av, t_server *server);

void            write_scene(t_scene *scene);


cl_float3		rotate_now(cl_float3 v);
void			write_feature(char *s, cl_float num, int fd);
void			write_pos_dir(cl_float3 dir, int fd);
void			write_pos_color_rot(cl_float3 pos,
					cl_float3 rot, cl_float3 color, int fd, cl_float3 v);
void			write_cam(t_cam cam, int fd);
void			write_light(t_obj obj, int fd);
void			write_texture(int id_mat, int id, int fd);
void			write_sphere(t_obj obj, int fd);
void			write_disk(t_obj obj, int fd);
void			write_cone(t_obj obj, int fd);
void			write_cylinder(t_obj obj, int fd);
void			write_plane(t_obj obj, int fd);
void			write_rectangle(t_obj obj, int fd);
void			write_torus(t_obj obj, int fd);
void			write_ellipse(t_obj obj, int fd);
void			write_triangle(t_obj obj, int fd);
void			write_parallelogram(t_obj obj, int fd);
void			write_which_obj(t_scene *scene, int i, int fd);


#endif
