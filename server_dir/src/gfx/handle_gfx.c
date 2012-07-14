/*
** handle_gfx.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Tue Jun 21 16:09:33 2011 dimitri jorge
** Last update Mon Jun 27 15:19:45 2011 dimitri jorge
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"
#include "gfx.h"

t_gfp	gl_cmd[] =
  {
    {"msz", gfx_get_mapsize},
    {"bct", gfx_get_frame},
    {"mct", gfx_get_all_frames},
    {"tna", gfx_get_teamnames},
    {"ppo", gfx_get_player_position},
    {"plv", gfx_get_player_level},
    {"pin", gfx_get_player_inventory},
    {"sgt", gfx_get_time_unit},
    {"sst", gfx_set_time_unit}
  };

int		handle_gfx(t_ctrl *c, t_jm_list *cli, char *s)
{
  unsigned int	i;

  i = 0;
  while (i < sizeof(gl_cmd) / sizeof(*gl_cmd))
    {
      if (!strncmp(gl_cmd[i].cmd, s, strlen(gl_cmd[i].cmd)))
	{
	  gl_cmd[i].p(c, cli, &s[strlen(gl_cmd[i].cmd)]);
	  return (1);
	}
      i++;
    }
  printf("Graphic client sent bad command '%s'\n", s);
  suc(cli);
  return (1);
}
