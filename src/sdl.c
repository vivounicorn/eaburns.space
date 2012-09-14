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

SDL_Surface *screen;

void init_sdl()
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    fprintf( stderr, "Could not initialize SDL: %s\n",
              SDL_GetError() );
    exit(-1);
  }

  atexit( SDL_Quit );

  screen = SDL_SetVideoMode( 648, 480, 16, SDL_SWSURFACE|SDL_ANYFORMAT);
  if( screen == NULL ) {
    fprintf( stderr, "Could not create SDL_Surface: %s\n",
              SDL_GetError() );
    exit(-1);
  }
}

void flip_screen()
{
  SDL_Flip( screen );
}

void clear_screen()
{
  SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0, 0, 0 ) );
}

Uint32 screen_width()
{
  return screen->w;
}

Uint32 screen_height()
{
  return screen->h;
}
