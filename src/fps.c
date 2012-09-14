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
#include <unistd.h>

#include "fps.h"
#include "font.h"
#include "color.h"
#include "data.h"
#include "sdl.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#define FPS_LIMIT 80
#define MAX_FPS_LEN 4
#define FPS_X screen_width() - 20
#define FPS_Y 0
#define FPS_FONT "FreeSans.ttf"
#define FPS_FONT_SIZE 10

static char *fontname = NULL;
static TTF_Font *fps_font;

static void close_fps();

void init_fps()
{
  /* Init font. */
  fontname = get_data( FPS_FONT, DATA_FONTS );
  fps_font = get_font( fontname, FPS_FONT_SIZE );
  free( fontname );

  /* Set a cleanup hook. */
  atexit(close_fps);
}

#define ROUND(x) (int)(x + .5)

void draw_fps()
{
  char fps_val[MAX_FPS_LEN];
  static Uint32 start_time = 0;
  static Uint32 fps_result = 0;
  static Uint32 fps_counter = 0;
  static Uint32 total_time = 0;

  Uint32 cur_time;
  Uint32 delta_time;
  Sint32 sleep_time = 0;

  if( start_time == 0 ) {
    start_time = SDL_GetTicks();
    return;
  }

  cur_time = SDL_GetTicks();
  delta_time = cur_time - start_time;
  start_time = cur_time;
  total_time += delta_time;

  sleep_time = ROUND((float)1000000/(float)FPS_LIMIT) - delta_time;


  if( FPS_LIMIT > 0 && sleep_time > 0 )
    usleep( sleep_time );

  if( total_time >= 1000 ) { /* One second has passed. */
    fps_result = fps_counter + 1;
    fps_counter = total_time = 0;
  }

  fps_counter++;

  sprintf( fps_val, "%d", fps_result );
  draw_text( fps_val, FPS_X, FPS_Y, fps_font,
             sdl_white, sdl_black );

}

static void close_fps()
{
  TTF_CloseFont( fps_font );
}
