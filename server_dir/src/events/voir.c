/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Thu Jul  7 16:44:43 2011 dimitri jorge
*/

#include <stdio.h>
#include "zappy.h"
#include "options.h"

static char	*gl_names[] =
  {
    "nourriture",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "joueur"
  };

static t_frame	*get_frame_by_dir_(t_ctrl *c, t_player *p, int i, int j)
{
  t_frame	*tmp;

  if (p->d == UP)
    tmp = get_elem_from_map(c, get_real_map_coord(p->x + j, getmapx(c)),
			    get_real_map_coord(p->y - i, getmapy(c)), ALL);
  else if (p->d == DOWN)
    tmp = get_elem_from_map(c, get_real_map_coord(p->x - j, getmapx(c)),
			    get_real_map_coord(p->y + i, getmapy(c)), ALL);
  else if (p->d == RIGHT)
    tmp = get_elem_from_map(c, get_real_map_coord(p->x + i, getmapx(c)),
			    get_real_map_coord(p->y + j, getmapy(c)), ALL);
  else
    tmp = get_elem_from_map(c, get_real_map_coord(p->x - j, getmapx(c)),
			    get_real_map_coord(p->y - i, getmapy(c)), ALL);
  return (tmp);
}

static void	write_frame_content_(t_ctrl *c, t_jm_list *cli,
				     t_player *p, int i, int j)
{
  t_frame	*tmp;

  tmp = get_frame_by_dir_(c, p, i, j);
  if (i != 0 || j != 0)
    jm_write(cli, ", ");
  while (tmp)
    {
      jm_write(cli, gl_names[tmp->type]);
      if (tmp->next)
	jm_write(cli, " ");
      tmp = tmp->next;
    }
}

int	voir(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  jm_write(cli, "{");
  while (i <= p->lvl)
    {
      j = -i;
      while (j <= i)
	{
	  write_frame_content_(c, cli, p, i, j);
	  ++j;
	}
      ++i;
    }
  jm_writeln(cli, "}");
  printf(GREEN"Player %d is looking arround"END, p->id);
  return (0);
}
