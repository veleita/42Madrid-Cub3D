#include "cub3D.h"

int		key_pressed(int keycode, t_key *key)
{
	if (keycode == A_KEY)
		key->a = 1;
	if (keycode == W_KEY)
		key->w = 1;
	if (keycode == S_KEY)
		key->s = 1;
	if (keycode == D_KEY)
		key->d = 1;
	if (keycode == LEFT_KEY)
		key->left = 1;
	if (keycode == RIGHT_KEY)
		key->right = 1;
	return (1);
}

int		key_released(int keycode, t_key *key)
{
	if (keycode == A_KEY)
		key->a = 0;
	if (keycode == W_KEY)
		key->w = 0;
	if (keycode == S_KEY)
		key->s = 0;
	if (keycode == D_KEY)
		key->d = 0;
	if (keycode == LEFT_KEY)
		key->left = 0;
	if (keycode == RIGHT_KEY)
		key->right = 0;
	if (keycode == ESC_KEY)
		ft_exit("Goodbye!");
	return (1);
}
