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
#include <SDL/SDL_image.h>
#include <stdlib.h>

#include "lifebar.h"
#include "sdl.h"
#include "data.h"
#include "ship.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#define BAR_IMAGE "lifebar.png"

/* The life bar image. */
SDL_Surface *bar = NULL;

/* Creates the lifebar. */
static void create_bar();

void draw_lifebar()
{
  SDL_Rect dr, sr;
  Uint32 life, max_life;
  float percent;

  life = get_life();
  max_life = get_max_life();
  percent = (float)life / (float)max_life;

  if( bar == NULL )
    create_bar();

  /* The portion of the origional image to display. */
  sr.x = 0;
  sr.y = bar->h - ((Sint32) ((float)percent * bar->h));
  sr.h = bar->h;
  sr.w = bar->w;

  /* Display position of the bar. */
  dr.x = screen_width() - bar->w - 5;
  dr.y = screen_height() - (sr.h - sr.y) - 5;

  SDL_BlitSurface( bar, &sr, screen, &dr );
}

static void create_bar()
{
  char *bar_path; 

  bar_path = get_data( BAR_IMAGE, DATA_IMAGES );
  bar = IMG_Load( bar_path );
  free( bar_path );
}
