#include "cub3D.h"

int main(int argc, char **argv)
{
  int	fd;
 
  /* Store the map file into the file descriptor (fd) */
  fd = open(argv[1], O_RDONLY);
  /* Initializates main variables */
  init(fd);
  /* Event hooks info
   * https://harm-smits.github.io/42docs/libs/minilibx/events.html
   *
   * KEY INPUT
   * These are called constantly while a key is being pressed (2 code)
   * or constantly while a key is being released (3 code)
   */
  mlx_hook(var->win, 2, 0, &key_pressed, var);
  mlx_hook(var->win, 3, 0, &key_released, var);
  /* MOVEMENT LOOP
   * This one is called constantly
   */
  mlx_loop_hook(var->mlx, &move_player, var);
  /* CLOSE THE WINDOW
   * The destroy notify event (17 code) notifies that a window is closed
   * https://tronche.com/gui/x/xlib/events/window-state-change/destroy.html
   */
  //mlx_hook(var_win, 17, 0, exit, var);
  /* Keep the program running */
  mlx_loop(var->mlx);
  // CHECK IF ALL THESE FUNCTIONS NEED TO BE PASSED THE WHOLE VAR STRUCT
  // CHECK IF THESE WOULD WORK WITH A MASK INSTEAD OF THE 0 VALUE
}
