/*
** handle_protocol_2.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Mon Jun 27 15:56:17 2011 dimitri jorge
** Last update Mon Jun 27 15:57:10 2011 dimitri jorge
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void	gfx_get_player_position(t_ctrl *c, t_jm_list *l, char *s)
{
  int	id;

  if (s[0] && s[1] && ((s[1] == '#' && s[2] && ((id = atoi(&s[2])) >= 1)) ||
		       ((id = atoi(&s[1])) >= 1)))
    ppo(c, l, id);
  else
    sbp(l);
}

void	gfx_get_player_level(t_ctrl *c, t_jm_list *l, char *s)
{
  int	id;

  if (s[0] && s[1] && ((s[1] == '#' && s[2] && ((id = atoi(&s[2])) >= 1)) ||
		       ((id = atoi(&s[1])) >= 1)))
    plv(c, l, id);
  else
    sbp(l);
}

void	gfx_get_player_inventory(t_ctrl *c, t_jm_list *l, char *s)
{
  int	id;

  if (s[0] && s[1] && ((s[1] == '#' && s[2] && ((id = atoi(&s[2])) >= 1)) ||
		       ((id = atoi(&s[1])) >= 1)))
    pin(c, l, id);
  else
    sbp(l);
}

void	gfx_get_time_unit(t_ctrl *c, t_jm_list *l, char *s)
{
  (void)s;
  sgt(c, l);
}

void	gfx_set_time_unit(t_ctrl *c, t_jm_list *l, char *s)
{
  int	val;

  if (!s[0] || !s[1] || !((val = atoi(&s[1])) >= 1))
    sbp(l);
  else
    sst(c, l, val);
}
