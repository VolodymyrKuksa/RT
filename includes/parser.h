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

# define NORMAL(a) (cl_float3){{a.x/LENGTH(a), a.y/LENGTH(a), a.z/LENGTH(a)}}
# define LENGTH(a) sqrt(a.x * a.x + a.y * a.y + a.z * a.z)
# define SUKA(x, y) ((x > y) ? x : y)

t_obj			default_parallelogram(void);
t_obj			default_sphere(void);
char			*read_file(int fd, size_t *size);
t_obj			default_cone(void);
t_obj			default_cylinder(void);
t_obj			default_plane(void);
t_obj			default_torus(void);
t_obj			default_rectangle(void);
t_obj			default_disk(void);
t_obj			default_paraboloid(void);
t_obj			default_triangle(void);

void			camera_default(t_cam *cam);
void			check_camera(t_cam *cam);
void			check_camera2(t_cam *cam);
void			get_cam_params2(char *name, json_value v, t_scene *scene);
void			get_camera_params(json_value *value, t_scene *scene);
void			fillthescene(json_value *value, t_scene *scene);

void			ftoa(float flt, int after_point, int xy, int fd);
void			error_fedun(char *er);
void			rot_pos_cam(cl_float3 *pos, cl_float3 rot);
void			minus_camera(cl_float3 *pos, cl_float3 cam_pos);
void			fill_position(char *name, cl_float value, cl_float3 *pos);
void			fill_color(char *name, cl_float value, t_obj *tmp);
void			check_tex_offs(cl_float2 tex_offs);
void			fill_col_distrupt(char *name, json_value v, t_obj *tmp);
void			init_rotate(t_basis *basis, cl_float3 rot);
void			checksumandemiss(t_obj *tmp);
void			check_basis(t_obj *tmp);
float			scalar_dobutok(cl_float3 a, cl_float3 b);
int				count_helping_obj(json_value *value);
void			parselight(json_value *value, t_obj *tmp);

void			fill_paraboloid_params(char *name, json_value v, t_obj *tmp);
void			fill_triangle_points(char *name, json_value v, t_obj *tmp);

void			fill_cone_hat1(t_scene *scene, t_obj tmp);
void			get_common_hat_cone(t_obj *obj1, t_obj tmp, t_scene *scene);
void			fill_cone_params(char *name, json_value v, t_obj *tmp);
void			fillthecone(json_value *value, t_scene *scene, int i);

void			fill_cylinder_params(char *name, json_value v, t_obj *tmp);
void			fill_plane_params(char *name, json_value v, t_obj *tmp);
void			fill_common(char *name, t_obj *tmp,
							json_value *v, cl_float3 *rot);
void			fill_basis(char *name, t_obj *tmp, cl_float v);
void			fill_cylind_hats(t_scene *scene, t_obj tmp);
void			fillthecylind(json_value *value, t_scene *scene, int i);
void			filltheplane(json_value *value, t_scene *scene, int i);
void			fillthesphere(json_value *value, t_scene *scene, int i);
void			filltorus(json_value *value, t_scene *scene, int i);
void			fillrectangle(json_value *value, t_scene *scene, int i);
void			filldisk(json_value *value, t_scene *scene, int i);
void			fillparaboloid(json_value *value, t_scene *scene, int i);
void			filltriangle(json_value *value, t_scene *scene, int i);
void			help_triangle(t_obj *tmp, t_scene *scene, cl_float3 rot);
cl_float3		normalize(cl_float3 vec);
cl_float3		cross(cl_float3 u, cl_float3 v);
void			get_basis(t_obj *obj);
void			fillparallelogram(json_value *value, t_scene *scene, int i);
void			rotate_scene_by_cam(t_scene *scene);
void			rotate_obj_by_camera(t_obj *tmp, cl_float3 rot);
void			parse_scene(int argc, char **argv,
							char **contents, size_t *len);
int				parse_server_data(int ac, char **av, t_server *server);
void			write_scene(t_scene *scene);
void			write_feature(char *s, cl_float num, int fd);
void			write_disrupt_tex_offs(t_obj obj, int fd);
void			fill_textures(char *name, t_obj *tmp, json_value v);
void			write_pos_color(cl_float3 pos, cl_float3 color, int fd);
void			write_cam_effect(t_cam cam, int fd);
void			write_cam(t_cam cam, int fd);
void			write_basis(t_obj obj, int fd);
void			write_light(t_obj obj, int fd);
void			write_texture(int id_mat, int id, int fd);
void			write_sphere(t_obj obj, int fd);
void			write_disk(t_obj obj, int fd);
void			write_cone(t_obj obj, int fd);
void			write_cylinder(t_obj obj, int fd);
void			write_plane(t_obj obj, int fd);
void			write_rectangle(t_obj obj, int fd);
void			write_torus(t_obj obj, int fd);
void			write_paraboloid(t_obj obj, int fd);
void			write_triangle(t_obj obj, int fd);
void			write_parallelogram(t_obj obj, int fd);
void			write_which_obj(t_scene *scene, int i, int fd);

#endif
