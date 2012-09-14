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

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "ship_types.h"
#include "xml.h"
#include "xml_tags.h"

/* Returns the SHIP_TYPE that has the name `t,' or NULL
 * if there is no ship type of that name. */
static SHIP_TYPE *get_ship_type( const char *t );

/* Enemy type list. */
static SHIP_TYPE *head = NULL;

void get_ships( const char *file )
{
  parse_xml( file );
}

void add_ship_type( SHIP_TYPE *t )
{
  t->next = head;
  head = t;
}

void free_ship_types()
{
  SHIP_TYPE *p;

  while( head != NULL ) {
    p = head;
    head = head->next;
    free( p );
  }
}

/* Getters for the SHIP_TYPE struct. */
char **get_center( const char *t )
{
  return get_ship_type( t )->center_frames;
}

char **get_left( const char *t )
{
  return get_ship_type( t )->left_frames;
}

char **get_right( const char *t )
{
  return get_ship_type( t )->right_frames;
}

Uint8 get_num_frames( const char *t )
{
  return get_ship_type( t )->num_frames;
}

Uint32 get_frame_delay( const char *t )
{
  return get_ship_type( t )->frame_delay;
}

Uint32 get_hp( const char *t )
{
  return get_ship_type( t )->hp;
}

Sint32 get_speed( const char *t ) 
{
  return get_ship_type( t )->speed;
}

Uint32 get_points( const char *t )
{
  return get_ship_type( t )->points;
}

MOVEMENT_PATTERN *get_move_funct( const char *t )
{
  return get_ship_type( t )->move_funct;
}

static SHIP_TYPE *get_ship_type( const char *t )
{
  SHIP_TYPE *p; 

  /* Find the ship type on the list. */  
  p = head;
  while( p != NULL && strcmp(p->name, t) != 0 )
    p = p->next;

  if( p != NULL && strcmp(p->name, t) == 0 )
    return p;

  fprintf( stderr, "Enemy type %s not found.\n", t );
  exit( 1 );
}
