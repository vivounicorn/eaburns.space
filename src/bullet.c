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

#include "bullet.h"
#include "bullet_types.h"
#include "sprite.h"
#include "config.h"
#include "enemy.h"
#include "size.h"
#include "data.h"
#include "explosion.h"

/* This dependency is wierd... but we need to know where to create the bullet. */
#include "ship.h" 

/* Linked list of bullets fired. */
static BULLET *head;

/* Number of bullets on the list. */
static Uint8 num_bullets = 0;

/* Gets the `i'th bullet from the list and returns it.  This fixes the
 * bug where if a bullet is removed while traversing the list there is
 * a discontinuity and a seg fault... Yet it sacrafices speed.  NULL is
 * returned if the bullet at index ``index'' is not found. */
static BULLET *get_bullet( Uint16 index );

void new_bullet( char *t )
{
  BULLET *p;
  char *image;
  static Uint32 time = 0;
  SPRITE *ship;

  ship = get_ship_sprite();

  if( time == 0 ) {
    time = SDL_GetTicks();

  } else {
    if( time + SHOOT_DELAY > SDL_GetTicks() )
      return;
    else
      time = SDL_GetTicks();
  }
  
  image = get_bullet_image( t );


  p = (BULLET*) malloc( sizeof( BULLET ) );
  p->sprite = new_sprite( ship->x + 
                ((ship->surface[ship->cur_frame]->w)/2),
                ship->y, 1, image, 50 );

  if( p->sprite == NULL ) {
    fprintf( stderr, "Error creating new sprite: %s.\n",
              SDL_GetError() );
    exit(-1);
  }

  set_speed( p->sprite, 3 );

  p->delay = get_bullet_delay( t );
  p->dammage = get_bullet_dammage( t );
  p->next = head;
  head = p;

  num_bullets++;
}

void delete_bullet( BULLET *b )
{
  BULLET *p, *j;

  for( p = j = head; p != NULL && p != b; j = p, p = p->next );

  if( p == NULL ) { return; }
  else if( p == head )
    head = head->next;
  else 
    j->next = p->next;

  free_sprite( p->sprite );         
  free( p );

  num_bullets--;
}

void draw_bullets()
{
  BULLET *p;
  ENEMY *e;
  Uint16 i;

  for( i = 0; i < num_bullets; i++ ) {

    p = get_bullet( i );
    if( p == NULL ) { break; }

    sprite_up( p->sprite );

    /* Remove sprite if it goes off of the top of the screen. */
    if( (p->sprite->y + p->sprite->surface[p->sprite->cur_frame]->h) < 0  ) {

      delete_bullet( p );
      continue;
    } else {
      draw_sprite( p->sprite );
      
    }

    /* Check for a bullet colliding with an enemy ship. */
    if( (e = check_enemy_collide( p->sprite )) != NULL ) {
      new_explosion( p->sprite->x, p->sprite->y, SMALL );
      hit_enemy( e, p->dammage );
      delete_bullet( p );
      continue;
    }
  }
  
}

static BULLET *get_bullet( Uint16 index )
{
  Uint16 i;
  BULLET *p;

  if( index > num_bullets ) { return NULL; }

  for( p = head, i = 0; p != NULL && i != index; p = p->next, i++ ); 

  if( i == index && p != NULL ) { return p; }

  return NULL;
}
