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

#include <stdarg.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

#include "sdl.h"
#include "sprite.h"
#include "side.h"

static SIDE _sprite_collide( SPRITE *s0, SPRITE *s1, Uint8 second );

SPRITE *new_sprite( int x, int y, Uint8 frames, ... )
{
  SPRITE *s;  
  Uint8 i;
  va_list args;
  char *arg;
  va_start( args, frames );

  s = (SPRITE*) malloc( sizeof(SPRITE) );

  /* Init the sprite struct. */
  s->x = x;
  s->y = y;
  s->speed = 1;
  s->flags = 0;
  s->frames = frames;
  s->cur_frame = 0;
  s->surface = (SDL_Surface**) malloc( sizeof(SDL_Surface) * frames );
  s->disp_time = 0;

  /* Load the surfaces. */
  for( i = 0; i < frames; i++ ) { 
    arg = va_arg( args, char* );
    s->surface[i] = IMG_Load( arg );

    if( s->surface[i] == NULL ) {
      free( s->surface[i] );
      free( s->surface );
      free( s );
      return NULL;
    }

  }

  /* Frame delay is the last arg. */
  s->frame_delay = (Uint32) va_arg( args, Uint32 );

  va_end( args );

  return s;
}

SPRITE *new_sprite_array( int x, int y, Uint8 frames, char** images, Uint32 frameRate )
{
  SPRITE *s;  
  Uint8 i;

  s = (SPRITE*) malloc( sizeof(SPRITE) );

  /* Init the sprite struct. */
  s->x = x;
  s->y = y;
  s->speed = 1;
  s->flags = 0;
  s->frames = frames;
  s->cur_frame = 0;
  s->surface = (SDL_Surface**) malloc( sizeof(SDL_Surface) * frames );
  s->disp_time = 0;

  /* Load the surfaces. */
  for( i = 0; i < frames; i++ ) { 
    s->surface[i] = IMG_Load( images[i] );

    if( s->surface[i] == NULL ) {
      free( s->surface[i] );
      free( s->surface );
      free( s );
      return NULL;
    }

  }

  s->frame_delay = frameRate;

  return s;
}

void free_sprite( SPRITE *s )
{
  Uint8 i;

  for( i = 0; i < s->frames; i++ )
    SDL_FreeSurface( s->surface[i] );
}

void draw_sprite( SPRITE *s )
{
  SDL_Rect dr;
  Uint32 time;

  time = SDL_GetTicks();

  /* Switch the frame if the frame delay has elapsed. */
  if( s->disp_time == 0 ) {
    s->disp_time = time;
  } else {
    if( time > s->disp_time + s->frame_delay ) {
      s->disp_time = time;
      s->cur_frame += 1; 
      s->cur_frame %= s->frames;
    }
  }

  /* Make a dest rectangle. */
  dr.x = s->x;
  dr.y = s->y;
  dr.w = s->surface[s->cur_frame]->w;
  dr.h = s->surface[s->cur_frame]->h;

  SDL_BlitSurface( s->surface[s->cur_frame], NULL, screen, &dr );
}

void no_off_screen( SPRITE *s )
{
  s->flags |= OFF_SCREEN_FLAG; 
}

void sprite_down( SPRITE *s )
{
  s->y += s->speed;

  if( s->flags & OFF_SCREEN_FLAG )
    if( s->y > (screen->h - s->surface[s->cur_frame]->h) )
      s->y = screen->h - s->surface[s->cur_frame]->h;
}

void sprite_up( SPRITE *s )
{
  if( s->flags & OFF_SCREEN_FLAG )
    s->y = (s->y < s->speed)? 0 : s->y - s->speed;
  else 
    s->y -= s->speed;
}

void sprite_left( SPRITE *s )
{
  if( s->flags & OFF_SCREEN_FLAG )
    s->x = (s->x < s->speed)? 0 : s->x - s->speed;
  else
    s->x -= s->speed;
}

void sprite_right( SPRITE *s )
{
  s->x += s->speed;

  if( s->flags & OFF_SCREEN_FLAG )
    if( s->x > (screen->w - s->surface[s->cur_frame]->w) )
      s->x = screen->w - s->surface[s->cur_frame]->w;
}

void set_speed( SPRITE *s, Sint32 speed )
{
  s->speed = speed;
}

/* Collision is checked s0 agains s1 then it recurses and checks s1 against s0
 * if there was no collision the other way.  This requires a flag argument
 * to tell the function not to test the swapped arguments for collision. 
 * hence this is just a wrapper function. */ 
SIDE sprite_collide( SPRITE *s0, SPRITE *s1 )
{
  return _sprite_collide( s0, s1, 0 );
}

/* This is the work function for sprite_collide, however it contains an
 * extra argument that is used as a flag for when the is the second call
 * to check collision and recursion needs to stop. */
static SIDE _sprite_collide( SPRITE *s0, SPRITE *s1, Uint8 second )
{
  Sint32 x0_0, y0_0, x0_1, y0_1;
  Sint32 x1_0, y1_0, x1_1, y1_1;
  SIDE retval = { 
    .none = 1,
    .top = 0,
    .bottom = 0,
    .left = 0,
    .right = 0
  };

  x0_0 = s0->x;
  x0_1 = x0_0 + s0->surface[s0->cur_frame]->w;
  y0_0 = s0->y;
  y0_1 = y0_0 + s0->surface[s0->cur_frame]->h;

  x1_0 = s1->x;
  x1_1 = x1_0 + s1->surface[s1->cur_frame]->w;
  y1_0 = s1->y;
  y1_1 = y1_0 + s1->surface[s1->cur_frame]->h;

  /* Check for horizontal overlap. */
  if( y0_0 < y1_1 && y0_0 > y1_0 ) { /* s0 top over s1 bottom. */
    if( second != 1 ) retval.top = 1;
    else retval.bottom = 1;
  } else if( y0_1 > y1_1 && y0_1 < y1_0 ) { /* s0 bottom over s1 top. */
    if( second != 1 ) retval.bottom= 1;
    else retval.top= 1;
  }

  /* Check for vertical overlap. */
  if( x0_0 > x1_0 && x0_0 < x1_1 ) {  /* s0 left over s1 right. */
    if( second != 1 ) retval.left = 1;
    else retval.right = 1;
  } else if( x0_1 < x1_0 && x0_1 > x1_1 ) { /* s0 right over s1 left. */
    if( second != 1 ) retval.right = 1;
    else retval.left = 1;
  }

  if( (retval.top + retval.bottom + retval.left + retval.right) >= 2 )
    retval.none = 0;  

  else if( second != 1 ) { return _sprite_collide( s1, s0, 1 ); }

  return retval;
}
