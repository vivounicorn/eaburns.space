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

#include <SDL/SDL.h> /* For Uint32 type. */
#include <stdlib.h>

#include "score.h"
#include "font.h"
#include "sdl.h"
#include "color.h"
#include "data.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

Uint32 player_score = 0;

#define SCORE_FONT "FreeSans.ttf"
#define SCORE_FONT_SIZE 15
#define SCORE_X 5
#define SCORE_Y 5
#define MAX_SCORE_LEN 20

static char *fontname = NULL;
static TTF_Font *score_font;

static void close_score();

void init_score()
{
  /* Get the font name and the font object ready for 
   * drawing. */
  fontname = get_data( SCORE_FONT, DATA_FONTS );
  score_font = get_font( fontname, SCORE_FONT_SIZE );
  free( fontname );

  /* Set a cleanup hook at exit. */
  atexit(close_score);
}

void draw_score()
{
  char score[MAX_SCORE_LEN];

  sprintf( score, "Score: %d", player_score );

  draw_text( score, SCORE_X, SCORE_Y, score_font, 
             sdl_white, sdl_black );
}

static void close_score()
{
  TTF_CloseFont( score_font );
}
