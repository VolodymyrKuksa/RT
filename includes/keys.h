/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:46:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/26 18:46:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

enum	e_keys
{
	NOKEY = 0,
	KEY_W = 1,
	KEY_S = 2,
	KEY_A = 4,
	KEY_D = 8,
	KEY_Q = 16,
	KEY_E = 32,
	KEY_UP = 64,
	KEY_DOWN = 128,
	KEY_RIGHT = 256,
	KEY_LEFT = 512,
	KEY_SPACE = 1024,
	KEY_C = 2048,
	KEY_ESC = 4096
};

#endif
