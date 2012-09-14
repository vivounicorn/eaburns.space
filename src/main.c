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
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sdl.h"
#include "sprite.h"
#include "ship.h"
#include "stars.h"
#include "planet.h"
#include "enemy.h"
#include "explosion.h"
#include "ship_types.h"
#include "font.h"
#include "data.h"
#include "arguments.h"
#include "score.h"
#include "fps.h"
#include "level.h"
#include "lifebar.h"
#include "bullet_types.h"

int main( int argc, char **argv )
{
  Uint8 *keys = NULL;
  char *xml_config;
  char *level;

  parse_args( argc, argv );

  /* Initialize everything. */
  init_sdl();
  init_fonts();
  init_score();
  init_fps();

  /* This is needed for stars and planet. */
  srand( (Uint32) time( NULL ) );

  /* Load the ship data out of the ships.xml file. */
  xml_config = get_data( SHIP_CONFIG, "." );
  get_ships( xml_config ); 
  free( xml_config );

  /* Load types of bullets. */
  xml_config = get_data( BULLET_CONFIG, "." );
  get_bullets( xml_config );
  free( xml_config );

  /* Create new ships... NOTE: This should be fixed. 
   * there should be levels. */
  new_ship( "dart" );  
  create_stars();
  create_planet();

  /* Check if the user specified a level or not.  If not then load
   * the first level. */
  if( user_level == NULL ) {
    level = get_data( "level1.xml", DATA_LEVELS );
    load_level( level );
    free( level );

  } else {
    load_level( user_level );
    free( user_level );
  }

/*
  new_enemy( 300, 0, "fighter" ); 
  new_enemy( 400, 0, "fighter_fast" ); 
  new_enemy( 300, -500, "fighter" ); 
  new_enemy( 400, -500, "fighter_fast" ); 
  new_enemy( 100, -900, "fighter_fast" ); 
*/

  while( 1 /* CONST COND */ ) {

    clear_screen();

    /* Draw order matters.  Things drawn last will
     * overlap things drawn before them. */
    draw_stars();
    draw_planet();
    draw_enemies();
    draw_ship();
    draw_explosions();
    draw_lifebar();
    draw_score();
    draw_fps();

    flip_screen();

    SDL_PumpEvents(); 
    keys = SDL_GetKeyState(NULL);

    /* Get keyboard events. */
    if( keys[SDLK_q] == 1 ) { break; }
    if( keys[SDLK_UP] == 1 ) { ship_up(); }
    if( keys[SDLK_DOWN] == 1 ) { ship_down(); }
    if( keys[SDLK_LEFT] == 1 ) { ship_left(); } 
    if( keys[SDLK_RIGHT] == 1 ) { ship_right(); }
    if( keys[SDLK_SPACE] == 1 ) { ship_shoot(); }

    /* If the ship is not moving left or right then it
     * should be centered. */
    if( !keys[SDLK_LEFT] && !keys[SDLK_RIGHT] )
      ship_center();
  }

  free_ship();
  SDL_Quit();

  return 0;
}
