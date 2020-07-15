#include "cub3D.h"

void	play(char *audio)
{
	char *play_audio;

	play_audio = ft_strjoin(PLAY, audio);
	while (true)
	{
		system(play_audio);
	}
}
