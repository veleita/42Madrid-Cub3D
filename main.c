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
  init(argv[1]);
/*   mlx_key_hook(var->win, 2, 0, &key_pressed, var); */
/*   mlx_key_hook(var->win, 3, 0, &key_released, var); */
/*   mlx_loop_hook(var->mlx, &move_player, var); */
/*   //mlx_hook(var_win, 17, 0, exit, var); */
/*   mlx_loop(var->mlx); */
}
