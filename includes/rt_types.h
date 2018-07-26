/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:12:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/23 19:12:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

#include <stdatomic.h>
# include "rt_textures.h"

# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netdb.h>
# include "libft.h"

typedef struct		s_env t_env;

typedef struct		s_scrn
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	t_rgb			*surf_arr;
}					t_scrn;

typedef struct		s_cam
{
	cl_float3		pos;
	cl_float3		dir;
	cl_float3		rot;
	cl_float3		updir;
	cl_float3		ldir;
	cl_float3		filter;
	double			fov;
	float			f_length;
	float			aperture;
	float			ratio;
	float			pr_pl_w;
	float			pr_pl_h;
	float			dust;
	float			brightness;
	float			refr_coef;
}					t_cam;

typedef struct		s_seed
{
	uint			*seeds;
	size_t			size;
}					t_seeds;

typedef struct		s_mvdata
{
	unsigned int	move_keys;
	float			move_spd;
	double			turn_a;
	double			cosine_a;
	double			sine_a;
}					t_mvdata;

typedef struct		s_ray
{
	cl_float3		pos;
	cl_float3		dir;
	int				refractions;
	float			dust;
}					t_ray;

typedef struct		s_quad
{
	float a;
	float b;
	float c;
	float d;
	float res;
}					t_quad;

typedef enum		e_obj_type
{
	sphere,
	plane,
	cylinder,
	cone,
	torus,
	disk,
	rectangle,
	ellipse,
	parallelogram,
	triangle
}					t_obj_type;

typedef struct		s_disk
{
	cl_float3	pos;
	cl_float	r;
}					t_disk;

typedef struct		s_sphere
{
	cl_float3	pos;
	cl_float	r;
}					t_sphere;

typedef struct		s_cylinder
{
	cl_float3	pos;
	float		r;
	float		h;
	float		tex_scale;
}					t_cylinder;

typedef struct		s_plane
{
	cl_float3	pos;
	float		tex_scale;
}					t_plane;

typedef struct		s_cone
{
	cl_float3	pos;
	float		tng;
	float		m1;
	float		m2;
	float		tex_scale;
}					t_cone;

typedef struct		s_torus
{
	cl_float3	pos;
	float		R;
	float		r;
}					t_torus;

typedef struct		s_ellipse
{
	cl_float3	c1;
	cl_float3	c2;
	float	r;
}					t_ellipse;

typedef struct		s_rectangle
{
	cl_float3	pos;
	float		h;
	float		w;
	float		tex_scale;
}					t_rectangle;

typedef struct		s_triangle
{
	cl_float3	d1;
	cl_float3	d2;
	cl_float3	d3;
}					t_triangle;

typedef struct		s_parallelogram
{
	cl_float3	pos;
	float		h;
	float		w;
	float		l;
}					t_parallelogram;

typedef	union		u_primitive
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_cone		cone;
	t_torus		torus;
	t_disk		disk;
	t_rectangle	rectangle;
	t_ellipse	ellipse;
	t_triangle	triangle;
	t_parallelogram	parallelogram;
}					t_primitive;

typedef struct		s_basis
{
	cl_float3		u;
	cl_float3		v;
	cl_float3		w;
}					t_basis;

enum				e_col_disrupt
{
	NODISRUPT,
	CHESS,
	COS,
	CIRCLE,
	PERLIN,
	PERLIN_RED,
	PERLIN_GREEN,
	PERLIN_BLUE
};

typedef struct		s_object
{
	t_obj_type	type;
	t_primitive	primitive;
	t_basis		basis;
	cl_float	diffuse;
	cl_float	specular;
	cl_float	refraction;
	cl_float	roughness;
	cl_float3	color;
	cl_float3	emission;
	int			tex_id;
	cl_float2	tex_offs;
	int			col_disrupt;
	int			mater_tex_id;
	cl_float3   rot;
}					t_obj;

typedef struct		s_scene
{
	int				num_obj;
	t_obj			*obj;
	t_cam			cam;
	int				cur_obj;
}					t_scene;

typedef struct		s_cldata
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	command_queue;
	char				*source[4];
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_size;
	size_t				local_size;

	cl_float3			*px_host;
	cl_float3			*pixels;
	pthread_mutex_t		pixel_lock;

	cl_mem				px_gpu;
	cl_mem				obj_gpu;
	cl_mem				seed_gpu;
	cl_mem				tx_gpu;
	cl_mem				txdata_gpu;

	t_seeds				seeds;
}					t_cldata;

typedef struct		s_client
{
	int					active;
	int					visual;
	int					socket_fd;
	int					portno;
	struct hostent		*server;
	struct sockaddr_in	server_addr;
	atomic_int			message_id;
}					t_client;

enum				e_status
{
	BUSY,
	FREE
};

enum				e_message
{
	STRING =     0b0,
	OBJ =        0b1,
	CAM =        0b10,
	TEXTURES =   0b100,
	TEX_DATA =   0b1000,
	PIXELS =     0b10000,
	WND_SIZE =   0b100000,
	CONNECTION = 0b1000000,
	QUIT =       0b10000000
};

typedef struct		s_client_queue
{
	int						client_fd;
	struct s_client_queue	*next;
}					t_client_queue;

typedef struct		s_message_queue
{
	enum e_message			type;
	unsigned int			size;
	void					*message;
	int						*destinations;
	size_t					dest_size;
	struct s_message_queue	*next;
}					t_message_queue;

typedef struct		s_thread
{
	int				thread_id;
	pthread_t		pid;
	unsigned int	status;
	unsigned int	alive;
	int				client_fd;
	char			*client_hostname;
	t_client_queue	**client_queue;
	pthread_mutex_t	*client_queue_lock;
	t_message_queue	**message_queue;
	pthread_mutex_t	*message_queue_lock;
	t_env			*env;
}					t_thread;

typedef struct		s_tpool
{
	unsigned int	total_threads;
	t_thread		*threads;
	t_client_queue	*client_queue;
	pthread_mutex_t	client_queue_lock;
	t_message_queue	*message_queue;
	pthread_mutex_t	message_queue_lock;
	t_env			*env;
}					t_tpool;

typedef struct		s_server
{
	atomic_int			active;
	pthread_t			pid;
	int					serv_socket_fd;
	int					port_no;
	struct sockaddr_in	serv_addr;
	unsigned int		num_threads;
	t_tpool				*tpool;
	atomic_int			message_id;
}					t_server;

typedef struct		s_env
{
	t_cldata			cl;
	t_scrn				screen;
	t_scene				scene;
	t_mvdata			mv_data;
	t_txgpu				textures;
	t_server			server;
	t_client			client;

	unsigned int		num_samples;
}					t_env;

#endif
