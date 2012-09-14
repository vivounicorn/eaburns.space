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

#include <SDL_ttf.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "font.h"
#include "sdl.h"

void init_fonts()
{
  if( TTF_Init() < 0 ) {
    fprintf( stderr, "Unable to initialzie SDL_ttf %s\n", SDL_GetError() );
    exit( 1 );
  }
  atexit( TTF_Quit );
}

TTF_Font *get_font( char *fontname, Sint32 size )
{
  TTF_Font *ret;

  ret = TTF_OpenFont( fontname, size );
  if( ret == NULL ) {
    fprintf( stderr, "Error opening font %s: %s.\n", fontname,
      SDL_GetError() );
    exit( 1 );
  }

  return ret;
}

void draw_text( const char *text, Uint32 x, Uint32 y, 
                TTF_Font *font, SDL_Color fg_color, 
                SDL_Color bg_color )
{
  SDL_Surface *surf;
  SDL_Rect dr;

  surf = TTF_RenderText_Shaded( font, text, fg_color, bg_color );
  //surf = TTF_RenderText_Solid( font, text, fg_color );

  dr.x = x;
  dr.y = y;

  SDL_BlitSurface( surf, NULL, screen, &dr ); 
}
