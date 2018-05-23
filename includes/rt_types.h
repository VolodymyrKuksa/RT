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

#include <SDL_video.h>
#include <SDL_system.h>
# include "libvec.h"

typedef struct		s_sphere
{
	t_vec			col;
	t_vec			pos;
	t_vec			emission;
	double			r;
}					t_sphere;

typedef struct		s_ray
{
	t_vec			pos;
	t_vec			dir;
}					t_ray;

typedef struct		s_cam
{
	t_vec			pos;
	t_vec			dir;
	t_vec			updir;
	t_vec			ldir;
	double			f_length;
	double			aperture;
}					t_cam;

typedef struct		s_env
{
	SDL_Window		*wnd;
	SDL_Renderer	*rend;
}					t_env;

#endif
