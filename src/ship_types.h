/*
 * Copyright (C) 2004, 2005 Ethan A. Burns <eaburns@cisunix.unh.edu>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <SDL/SDL.h>

#include "m_pattern.h"

#ifndef _SHIP_TYPE_H_ 
#define _SHIP_TYPE_H_ 

typedef struct _SHIP_TYPE {
  char *name; /* Used to identify the ship. */

  /* Paths to each frame for the animation of the ship
   * while facing front and center, left, and right. */
  char **center_frames;
  char **left_frames;
  char **right_frames;
  Uint8 num_frames;
  Uint32 frame_delay; /* Delay between animation frames. */

  Uint32 hp; /* Number of ship hp. */
  Sint32 speed; /* Speed of the ship. */
  Uint32 points; /* Number of points for the ship type. */

  /* The movement callback function for enemies. */
  MOVEMENT_PATTERN *move_funct;

  struct _SHIP_TYPE *next; 
} SHIP_TYPE;

#endif /* _SHIP_TYPE_H_ */

/* Reads the ships from an .xml file. */
void get_ships( const char *file );

/* Adds an SHIP_TYPE to the list. */
void add_ship_type( SHIP_TYPE *t );

/* Frees the ship type list. */
void free_ship_types();

/* Getters for the SHIP_TYPE struct. */
char **get_center( const char *t );
char **get_left( const char *t );
char **get_right( const char *t );
Uint8 get_num_frames( const char *t );
Uint32 get_frame_delay( const char *t );
Uint32 get_hp( const char *t );
Sint32 get_speed( const char *t );
Uint32 get_points( const char *t );
MOVEMENT_PATTERN *get_move_funct( const char *t );
