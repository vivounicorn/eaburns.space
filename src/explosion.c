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
#include <stdlib.h>

#include "size.h"
#include "explosion.h"
#include "data.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/* Head of the explosion list. */
static EXPLOSION *head = NULL;

/* Number of explosions in the list. */
static Uint16 num_explosions = 0;

/* Returns a pointer to the explosion on the list at index ``index''
 * or NULL is returned if the index is invalid. */
static EXPLOSION *get_explosion( Uint16 index );

/* Removes an explosion `e' from the list. */
static void remove_explosion( EXPLOSION *e );

#define EXPLOSION_MAX_PATH_LEN 100

void new_explosion( Sint32 x, Sint32 y, SIZE s )
{
  EXPLOSION *e;
  char *path[EXPLOSION_FRAMES]; 
  char temp[MAX_PATH_LEN];
  Uint8 i;
  
  switch( s ) {
  case SMALL:
    for( i = 0; i < EXPLOSION_FRAMES; i++ ) {
      sprintf( temp, "%s%d%s", EXPLOSION_SMALL, i, EXPLOSION_EXTENTION ); 
      path[i] = get_data( temp, DATA_IMAGES );
    }
    break;

  case MEDIUM:
    for( i = 0; i < EXPLOSION_FRAMES; i++ ) {
      sprintf( temp, "%s%d%s", EXPLOSION_MEDIUM, i, EXPLOSION_EXTENTION ); 
      path[i] = get_data( temp, DATA_IMAGES );
    }
    break;

  case BIG:
    for( i = 0; i < EXPLOSION_FRAMES; i++ ) {
      sprintf( temp, "%s%d%s", EXPLOSION_BIG, i, EXPLOSION_EXTENTION ); 
      path[i] = get_data( temp, DATA_IMAGES );
    }
    break;
  }

  e = (EXPLOSION*) malloc( sizeof( EXPLOSION ) );
  e->sprite = new_sprite_array( x, y, EXPLOSION_FRAMES, path, EXPLOSION_RATE );
  if( e == NULL ) {
    fprintf( stderr, "Error creating new sprite: %s.\n",
              SDL_GetError() );
    exit(-1);
  }

  for( i = 0; i < EXPLOSION_FRAMES; i++ )
    free( path[i] );

  e->last_frame = 0;
  e->next = head;
  head = e;   

  num_explosions++;
}

void draw_explosions()
{
  Uint16 i;
  EXPLOSION *p;

  for( i = 0; i < num_explosions; i++ ) {

    p = get_explosion( i );

    /* Check for animation over. */
    if( p->sprite->cur_frame < p->last_frame ) {
      remove_explosion( p );

    } else {
  
      /* Draw the explosion. */
      p->last_frame = p->sprite->cur_frame;
      draw_sprite( p->sprite );
    }

  }
}

static void remove_explosion( EXPLOSION *e )
{
  EXPLOSION *p, *j;

  for( p = j = head; p != NULL && p != e; j = p, p = p->next );

  if( p == NULL ) { return; }
  else if ( p == head ) {
    head = head->next;

  } else {
    j->next = p->next;

  }

  free_sprite( p->sprite );
  free( p );

  num_explosions--;
}

static EXPLOSION *get_explosion( Uint16 index )
{
  Uint16 i;
  EXPLOSION *p;

  if( index > num_explosions ) { return NULL; }

  for( p = head, i = 0; p != NULL && i != index; p = p->next, i++ ); 

  if( i == index && p != NULL ) { return p; }

  return NULL;
}
