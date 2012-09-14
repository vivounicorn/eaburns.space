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
#include <string.h>
#include <stdlib.h>

#include "ship.h"
#include "sprite.h"
#include "sdl.h"
#include "explosion.h"
#include "side.h"
#include "bullet.h"
#include "ship_types.h"
#include "gameover.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/* Number of milliseconds between registering ship collisions.
 * If this is set to zero, the ship pretty much dies instantly
 * after getting hit. */
#define SHIP_HIT_TIMEOUT 200

/* Player gets twice the hp of a normal ship. */
#define PLAYER_HP_FACTOR 2 

typedef struct {

  /* The current ship sprite. */
  SPRITE *current;
  
  /* The sprite dirrection images. */
  SPRITE *left;
  SPRITE *right;
  SPRITE *center;

  Uint32 hp;  /* HP of the ship. */
  Uint32 hp_max; /* Maximum HP of the ship. */

  char *type; /* Type of ship. */

} SHIP;

static SHIP ship;

void new_ship( char *t )
{
  Sint32 frames;
  Sint32 delay;
  Sint32 speed;
  Sint32 x, y;

  x = screen_width() / 2;
  y = screen_height() - 50;

  frames = get_num_frames( t );
  delay = get_frame_delay( t );
  speed = get_speed( t );
  ship.hp = get_hp( t ) * PLAYER_HP_FACTOR; 
  ship.hp_max = ship.hp;
  ship.type = strdup( t );

  ship.left = new_sprite_array( x, y, frames, get_left( t ), delay );
  if( ship.left == NULL ) { 
    fprintf( stderr, "Error creating new sprite: %s.\n", SDL_GetError() );
    exit( 1 );
  }
  set_speed( ship.left, speed );
  no_off_screen( ship.left );

  ship.right = new_sprite_array( x, y, frames, get_right( t ), delay );
  if( ship.right == NULL ) { 
    fprintf( stderr, "Error creating new sprite: %s.\n", SDL_GetError() );
    exit( 1 );
  }
  set_speed( ship.right, speed );
  no_off_screen( ship.right );

  ship.center = new_sprite_array( x, y, frames, get_center( t ), delay );
  if( ship.center == NULL ) { 
    fprintf( stderr, "Error creating new sprite: %s.\n", SDL_GetError() );
    exit( 1 );
  }
  set_speed( ship.center, speed );
  no_off_screen( ship.center );

  ship.current = ship.center;
  ship_center();
}

void free_ship()
{
  free( ship.type );
  free_sprite( ship.center );
  free_sprite( ship.left );
  free_sprite( ship.right );
}

void draw_ship()
{
  draw_bullets();
  draw_sprite( ship.current );
}

void ship_center()
{
  ship.center->x = ship.current->x;
  ship.center->y = ship.current->y;
  ship.current = ship.center;
}

void ship_left()
{
  ship.left->x = ship.current->x;
  ship.left->y = ship.current->y;
  ship.current = ship.left;
  sprite_left( ship.current ); 
}

void ship_right()
{
  ship.right->x = ship.current->x;
  ship.right->y = ship.current->y;
  ship.current = ship.right;
  sprite_right( ship.current ); 
}

void ship_up()
{
  ship_center();
  sprite_up( ship.current ); 
}

void ship_down()
{
  ship_center();
  sprite_down( ship.current ); 
}

void ship_shoot()
{
  new_bullet( "machine_gun" );
}

SPRITE *get_ship_sprite()
{
  return ship.current; 
}

void ship_hit( SIDE side )
{
  static Uint32 last_hit = 0;

  if( last_hit == 0 ) {
    last_hit = SDL_GetTicks();

  } else {
    if( last_hit + SHIP_HIT_TIMEOUT > SDL_GetTicks() )
      return;
    else
      last_hit = SDL_GetTicks();
  }

  new_explosion( ship.current->x, ship.current->y, SMALL );
  ship.hp -= 2;

  if( ship.hp <= 0 ) {
    game_over();
  }
}

Uint32 get_life()
{
  return ship.hp;
}

Uint32 get_max_life()
{
  return ship.hp_max;
}
