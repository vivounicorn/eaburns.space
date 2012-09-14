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

#include "sdl.h"
#include "stars.h"

#define NUM_STARS 20
#define BIG_STAR_SIZE 4

static STAR stars[NUM_STARS];

/* Draw stars of different sizes. */
static void big_star( Uint32 x, Uint32 y );
static void med_star( Uint32 x, Uint32 y );
static void small_star( Uint32 x, Uint32 y );

void create_stars()
{
  Uint8 i;

  for( i = 0; i < NUM_STARS; i++ ) {
    stars[i].size = ( rand() % BIG ) + SMALL;  /* a random size. */    
    stars[i].x = ( rand() % screen_width() );  /* a random x coord. */
    stars[i].y = ( rand() % screen_height() ); /* a random y coord. */
    stars[i].speed = ( rand() % 3 ) + 1;       /* a random speed. */
  }
}

void draw_stars()
{
  Uint8 i;
  for( i = 0; i < NUM_STARS; i++ ) {
    switch( stars[i].size ) {
    case SMALL: small_star( stars[i].x, stars[i].y ); break;
    case MEDIUM: med_star( stars[i].x, stars[i].y ); break;
    case BIG: big_star( stars[i].x, stars[i].y ); break;
    }

    stars[i].y += stars[i].speed;
    if( stars[i].y > screen_height() - BIG_STAR_SIZE ) {
      stars[i].size = ( rand() % BIG ) + SMALL;  /* a random size. */    
      stars[i].x = ( rand() % screen_width() );  /* a random x coord. */
      stars[i].y = 0;
      stars[i].speed = ( rand() % 3 ) + 1;       /* a random speed. */
    }
  }
}

static void big_star( Uint32 x, Uint32 y )
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.h = BIG_STAR_SIZE;
  rect.w = BIG_STAR_SIZE;
  SDL_FillRect( screen, &rect, SDL_MapRGB( screen->format, 255, 255, 255 ) ); 
}

static void med_star( Uint32 x, Uint32 y )
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.h = BIG_STAR_SIZE - 1;
  rect.w = BIG_STAR_SIZE - 1;
  SDL_FillRect( screen, &rect, SDL_MapRGB( screen->format, 255, 255, 255 ) ); 
}

static void small_star( Uint32 x, Uint32 y )
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.h = BIG_STAR_SIZE - 2;
  rect.w = BIG_STAR_SIZE - 2;
  SDL_FillRect( screen, &rect, SDL_MapRGB( screen->format, 255, 255, 255 ) ); 
}
