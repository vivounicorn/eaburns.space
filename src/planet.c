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

#include "sprite.h"
#include "planet.h"
#include "sdl.h"
#include "data.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

static SPRITE *planet = NULL;

/* Number of types of planets */
#define PLANET_IMAGE_NUM 1
#define PLANET_SPEED 1

#define MOON_1_IMAGE "moon1.png"

void create_planet()
{
  Uint32 x, y;
  Uint32 i;
  char *image = NULL;

  /* Get random coordinates. */
  x = ( rand() % screen_width() );
  y = -( rand() % 1000) + 100;

  /* Get random image name. */
  i = ( rand() % PLANET_IMAGE_NUM ) + 1; 
  switch( i ) {
  case 1: image = get_data( MOON_1_IMAGE, DATA_IMAGES ); break;
  default: image = NULL;
  }

  /* Make the planet sprite. */
  planet = new_sprite( x, y, 1, image, 0 );
  set_speed( planet, PLANET_SPEED ); 
  if( planet == NULL ) {
    fprintf( stderr, "Error creating new sprite: %s.\n",
              SDL_GetError() );
    exit(-1);
  }
}

void draw_planet()
{
  if( planet->y > (Sint32)screen_height() )
    create_planet();

  draw_sprite( planet );
  sprite_down( planet );
}
