/*
** get_real_map_coord.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Sat Jun 18 17:57:50 2011 jose rodrigues
** Last update Sun Jun 19 17:06:34 2011 dimitri jorge
*/

#include "zappy.h"

int	get_real_map_coord(int c, int max)
{
  while (c < 0)
    c = max + c;
  return (c % max);
}
