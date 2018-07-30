/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 11:46:28 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/25 11:46:28 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# define FONT "gui_textures/BebasNeue-Regular.ttf"

# include <SDL_ttf.h>
# include <SDL_image.h>
# include <stdarg.h>
# include "libft.h" 

/* char type 0 - button, 1 - menu */

typedef struct          s_gui_obj
{
    float               x;
    float               y;
    SDL_Rect            my_rect;
    struct s_gui_obj    *father;
    char                type;
    void                (*action)(void *some_shit, SDL_Renderer *renderer);
}                       t_gui_obj;

typedef enum            e_menu_type
{
    GLOBAL_MENU,
    OBJECTS_MENU
}                      menu_type;

SDL_Rect                init_rect(int x, int y, int w, int h);
int                     check_click(int x, int y, t_gui_obj *gui_obj);


/*--------------------------Mouse-----------------------------*/
typedef struct          s_mouse
{
    int                 dx;
    int                 dy;
}                       t_mouse;
/*------------------------------------------------------------*/

/*--------------------------Label-----------------------------*/
typedef struct          s_label
{
    float               x;
    float               y;
    float               width;
    float               height;
    char                *text;
    unsigned char       font_size;
    TTF_Font            *font;
    SDL_Texture         *texture;
    SDL_Rect            dstrect;
    t_gui_obj           *father;

    void                (*draw)(SDL_Renderer *renderer, struct s_label *my_label);
    void                (*update)(struct s_label *my_label, char with_text, SDL_Renderer *renderer, char with_alph);
}                       t_label;


t_label                 create_label(unsigned short int x, unsigned short int y, char *text, t_gui_obj *father);
void                    label_settings(int font_size, SDL_Renderer *renderer, t_label *my_label, int set_wh);
void                    draw_label(SDL_Renderer *renderer, t_label *label);
void                    update_label(t_label *my_label, char with_text, SDL_Renderer *renderer, char with_alph);
void                    destroy_label(  t_label *my_label);
/*------------------------------------------------------------*/

/*--------------------------Button----------------------------*/
typedef struct          s_button
{
    float               x;
    float               y;
    SDL_Rect            my_rect;
    t_gui_obj           *father;
    char                type;
    void                (*action)(void *some_shit, SDL_Renderer *renderer);
    /*                  */
    char                *source;
    t_label             name;
    SDL_Texture         *texture;

    void                (*draw)(SDL_Renderer *renderer, struct s_button *my_button);
    void                (*update)(struct s_button *my_button, char with_text, SDL_Renderer *renderer, char with_alph);
    t_gui_obj           *(*collision)(int x, int y, t_gui_obj *gui_obj);
}                       t_button;

t_button                create_button(SDL_Rect my_rect, t_gui_obj *father, char *text);
void                    button_settings(SDL_Renderer *renderer, t_button *my_button);
void                    button_set_label(char *text, int font_size, SDL_Renderer *renderer, t_button *my_button);
void                    draw_button(SDL_Renderer *renderer, t_button *my_button);
t_gui_obj               *check_button_collision(int x, int y, t_gui_obj *gui_obj);
void                    update_button(t_button *my_button, char with_text, SDL_Renderer *renderer, char with_alph);
void                    destroy_button(t_button *my_button);
/*------------------------------------------------------------*/

/*--------------------------Button-Types----------------------*/

/*--------------------------ValueController-------------------*/
typedef struct          s_value_controler
{
    float               x;
    float               y;
    SDL_Rect            my_rect;
    t_gui_obj           *father;
    char                type;
    void                (*action)(void *some_shit, SDL_Renderer *renderer); //проверить на необходимость холостых функций
    /*                  */
    char                *source;
    t_label             output;
    SDL_Texture         *texture;
    t_button            change_buttons[2];
    float               *value;
    char                *val_name;
    float               max_val;
    float               min_val;
    float               step;

    void                (*draw)(SDL_Renderer *renderer, struct s_value_controler *my_control);
    void                (*update)(struct s_value_controler *my_control, char with_text, SDL_Renderer *renderer, char with_alph);
    t_gui_obj           *(*collision)(int x, int y, t_gui_obj *gui_obj);
}                       t_val_control;

t_val_control           create_controller(SDL_Rect my_rect, t_gui_obj *father, char *text, float *value);
void                    controller_own_set(SDL_Renderer *renderer, t_val_control *my_control);
void                    more_controler_settings(t_val_control *my_control, float max_val, float min_val, char *val_name);
void                    controller_settings(t_val_control *my_control, SDL_Renderer *renderer, float step);
void                    update_controler(t_val_control *my_control, char with_text, SDL_Renderer *renderer, char with_alph);
void                    draw_controler(SDL_Renderer *renderer, t_val_control *my_control);
t_gui_obj               *check_contol_collision(int x, int y, t_gui_obj *gui_obj);
void                    plus_action(void *some_shit, SDL_Renderer *renderer);
void                    minus_action(void *some_shit, SDL_Renderer *renderer);
void                    destroy_controller(t_val_control *my_control);
/*------------------------------------------------------------*/

/*-----------------------RadioButton--------------------------*/
typedef struct          s_radio_button
{
    float               x;
    float               y;
    SDL_Rect            my_rect;
    t_gui_obj           *father;
    char                type;
    void                (*action)(void *some_shit, SDL_Renderer *renderer); //аналогично
    /*                  */
    char                *source;
    t_label             pointer;
    SDL_Texture         *texture;
    t_button            *buttons;
    int                 last_pressed;
    int                 num_of_buttons;
    int                 *value;

    void                (*draw)(SDL_Renderer *renderer, struct s_radio_button *my_radio);
    void                (*update)(struct s_radio_button *my_radio, char with_text, SDL_Renderer *renderer);
    t_gui_obj           *(*collision)(int x, int y, t_gui_obj *gui_obj);
}                       t_radio_button;

t_radio_button          create_radio(SDL_Rect my_rect, t_gui_obj *father, char *text, int *value);
void                    radio_own_set(SDL_Renderer *renderer, t_radio_button *my_radio);
void                    radio_settings(t_radio_button *my_radio, SDL_Renderer *renderer, int number, ...);
void                    update_radio(t_radio_button *my_radio, char with_text, SDL_Renderer *renderer);
void                    draw_radio(SDL_Renderer *renderer, t_radio_button *my_radio);
t_gui_obj               *check_radio_collision(int x, int y, t_gui_obj *gui_obj);
void                    radio_action(void *some_shit, SDL_Renderer *renderer);
void                    destroy_radio(t_radio_button *my_radio);
/*------------------------------------------------------------*/

/*------------------------------------------------------------*/

#endif  