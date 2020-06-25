#include "cub3D.h"

/*
** L24: init() initializates main variables
**
** Event hooks info
** https://harm-smits.github.io/42docs/libs/minilibx/events.html
**
** L25: KEY INPUT
** These are called constantly while a key is being pressed (2 code)
** or constantly while a key is being released (3 code) 
**
** L27: MOVEMENT LOOP
** 	This one is called constantly 
**
** L28: CLOSE THE WINDOW
** 	The destroy notify event (17 code) notifies that a window is closed
** 	https://tronche.com/gui/x/xlib/events/window-state-change/destroy.html
**
** L29: KEEP THE PROGRAM RUNNING
*/
int main(int argc, char **argv)
{
  t_var *var;
  
  if (!(var = (t_var*)malloc(sizeof(t_var))))
    ft_exit ("Failed to allocate memory for the var struct (init.c)"); 
  init(argv[1], var);
  mlx_hook(var->id->win, 2, 1L<<0, &key_pressed, var->key);
  mlx_hook(var->id->win, 3, 1L<<1, &key_released, var->key);
  mlx_loop_hook(var->id->mlx, &move_player, var);
  mlx_loop(var->id->mlx);
}
