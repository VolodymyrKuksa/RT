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
# include "libvec.h"

# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netdb.h>
# include "libft.h"
# include "gui.h"

typedef struct		s_env t_env;

typedef struct		s_scrn
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Renderer	*renderer;
	t_rgb			*surf_arr;
}					t_scrn;

enum				e_effects
{
	NOEFFECT,
	BLACK_N_WHITE,
	NEGATIVE,
	SEPIA,
	CARTOON
};

typedef struct		s_cam
{
	cl_float3		pos;
	cl_float3		dir;
	cl_float3		rot;
	cl_float3		updir;
	cl_float3		ldir;
	cl_float3		filter;	//
	double			fov;	//
	float			f_length;
	float			aperture;
	float			ratio;
	float			pr_pl_w;
	float			pr_pl_h;
	float			dust;	//
	float			brightness;	//
	float			refr_coef;	//
	int				effect;		//
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
	t_vec		pos;
	t_vec		dir;
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
	parallelogram,
	triangle,
	elipsoid
}					t_obj_type;

typedef struct		s_disk
{
	cl_float3	pos;
	cl_float	r;
	int			related;
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

typedef struct		s_rectangle
{
	cl_float3	pos;
	float		h;
	float		w;
	float		tex_scale;
}					t_rectangle;

typedef struct		s_parallelogram
{
	cl_float3	pos;
	float		h;
	float		w;
	float		l;
}					t_parallelogram;

typedef struct		s_triangle
{
	cl_float3	d1;
	cl_float3	d2;
	cl_float3	d3;
}					t_triangle;

typedef struct		s_elipsoid
{
	cl_float3	pos;
	cl_float3	c1;
	cl_float3	c2;
	float 		r;
}					t_elipsoid;

typedef	union		u_primitive
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_cone			cone;
	t_torus			torus;
	t_disk			disk;
	t_rectangle		rectangle;
	t_parallelogram	parallelogram;
	t_triangle		triangle;
	t_elipsoid		elipsoid;
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
	cl_program			pr_intersect;
	cl_kernel			kernel;
	cl_kernel			kr_intersect;
	size_t				global_size;
	size_t				local_size;

	int					*id_host;
	cl_float3			*px_host;
	cl_float3			*pixels;
	pthread_mutex_t		pixel_lock;

	cl_mem				px_gpu;
	cl_mem				obj_gpu;
	cl_mem				seed_gpu;
	cl_mem				tx_gpu;
	cl_mem				txdata_gpu;
	cl_mem				id_gpu;

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

/*--------------------------Menu------------------------------*/
typedef struct          s_gui_menu
{
    float               x;
    float               y;
    SDL_Rect            my_rect;
    t_gui_obj           *father;
    char                type;
    void                (*action)(void *some_shit, SDL_Renderer *renderer);
    /*                  */
    t_scene             *scene;
    menu_type           m_type;
    t_mouse             *mouse;
    char                *source;
    SDL_Texture         *texture;
    t_button            main_button;
    unsigned char       numb_of_labels;
    unsigned char       numb_of_control;
    unsigned char       numb_of_radio;

    t_radio_button      *radio;
    t_val_control       *controls;
    t_label             *labels;

    void                (*draw)(SDL_Renderer *renderer, struct s_gui_menu *my_radio);
    void                (*update)(struct s_gui_menu *my_menu, char with_text, SDL_Renderer *renderer, char hide);
    t_gui_obj           *(*collision)(int x, int y, t_gui_obj *gui_obj);
}                       t_gui_menu;

t_gui_menu              create_menu(int x, int y, char *text, t_mouse *mouse);
void                    menu_own_set(SDL_Renderer *renderer, t_gui_menu *my_menu);
void                    menu_settings(t_gui_menu *my_menu, SDL_Renderer *renderer, menu_type type, t_scene *scene);
void                    unhide_objects_menu(void *some_shit, SDL_Renderer *renderer);
void                    unhide_global_menu(void  *some_shit, SDL_Renderer *renderer);
void                    fill_global_menu(t_gui_menu *my_menu, SDL_Renderer *renderer);
void                    fill_objects_menu(t_gui_menu *my_menu, SDL_Renderer *renderer);
void                    update_menu(t_gui_menu *my_menu, char with_text, SDL_Renderer *renderer, char hide);
void                    draw_menu(SDL_Renderer *renderer, t_gui_menu *my_menu);
t_gui_obj               *check_menu_collision(int x, int y, t_gui_obj *gui_obj);
void                    hide_menu(void *some_shit, SDL_Renderer *renderer);
void                    menu_action(void *some_shit, SDL_Renderer *renderer);
void                    destroy_menu(t_gui_menu *my_menu, SDL_Renderer *renderer);
/*------------------------------------------------------------*/

/*---------------------------MainGuiType----------------------*/
typedef struct          s_gui
{
    t_gui_menu          *menu;
    t_button            *button;
    t_label             *label;
    t_mouse             *mouse;

    unsigned char       numb_of_menus;
    unsigned char       numb_of_buttons;
    unsigned char       numb_of_labels;
	
	void				(*draw)(SDL_Renderer *renderer, struct s_gui *my_gui);
	void				(*update)(struct s_gui *my_gui, SDL_Renderer *renderer);
	t_gui_obj			*(*collision)(int x, int y, t_gui_obj *gui_obj);
}                       t_gui;

t_gui             		init_gui(SDL_Renderer *renderer, t_scene *scene);
void                	draw_gui(SDL_Renderer *renderer, t_gui *my_gui);
t_gui_obj           	*check_gui_collision(int x, int y, t_gui_obj *gui_obj);
void                	update_gui(t_gui *my_gui, SDL_Renderer *renderer);
void                	destroy_gui(t_gui *my_gui, SDL_Renderer *renderer);
/*------------------------------------------------------------*/

typedef struct		s_env
{
	t_cldata			cl;
	t_gui				gui;
	t_scrn				screen;
	t_scene				scene;
	t_mvdata			mv_data;
	t_txgpu				textures;
	t_server			server;
	t_client			client;
	unsigned int		num_samples;
}					t_env;

#endif
