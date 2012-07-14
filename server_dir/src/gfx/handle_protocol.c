/*
** msz.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Tue Jun 21 18:55:03 2011 dimitri jorge
** Last update Mon Jun 27 15:57:12 2011 dimitri jorge
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void	gfx_get_mapsize(t_ctrl *c, t_jm_list *l, char *s)
{
  (void)s;
  msz(c, l);
}

void	gfx_get_frame(t_ctrl *c, t_jm_list *l, char *s)
{
  int	i;

  i = 1;
  if (!s[0] || !s[1] || (s[1] && !(s[1] >= '0' && s[1] <= '9')))
    sbp(l);
  else
    {
      while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	i++;
      if (s[i] && s[i + 1] && s[i + 1] >= '0' && s[i + 1] <= '9')
	bct(c, l, atoi(&s[1]), atoi(&s[i + 1]));
      else
	sbp(l);
    }
}

void	gfx_get_all_frames(t_ctrl *c, t_jm_list *l, char *s)
{
  (void)s;
  mct(c, l);
}

void	gfx_get_teamnames(t_ctrl *c, t_jm_list *l, char *s)
{
  (void)s;
  tna(c, l);
}

