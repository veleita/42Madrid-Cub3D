#include "cub3D.h"

static void	bubble_sort(int *list, double *content, int elements)
{
	int 	it;
	int 	add;
	int	list_copy;
	double	content_copy;

	it = 0;
	while (it < elements)
	{
		add = it;
		while (++add < elements)
		{
			if ( content[it] > content[add])
			{
				list_copy = list[it];
				list[it] = list[add];
				list[add] = list_copy;
				content_copy = content[it];
				content[it] = content[add];
				content[add] = content_copy;
			}
		}
		it++;
	}
}

void		order_sprites(int num_sprites, t_sprite **sprite, double pos_x, double pos_y)
{
	int 	sprite_order[num_sprites];
	double	sprite_distance[num_sprites];
	int	it;

	it = 0;
	while (it < num_sprites)
	{
		sprite_order[it] = it;
		sprite_distance[it] = sqrt((pos_x - sprite[it]->pos_x) * (pos_x - sprite[it]->pos_x)
				+ (pos_y - sprite[it]->pos_y) * (pos_y - sprite[it]->pos_y));
		it++;
	}
	bubble_sort(sprite_order, sprite_distance, num_sprites);
	it = 0;
	while (it < num_sprites)
	{
		printf("sprite %d - distance %f\n", sprite_order[it], sprite_distance[it]);
		it++;
	}
	printf("\n");
}
