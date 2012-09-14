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

#include "sprite.h"
#include "size.h"

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

typedef struct _EXPLOSION {

  SPRITE *sprite; /* The sprite for the explosion. */
  Uint8 last_frame; /* last frame displayed (for checking for an animation loop). */
  struct _EXPLOSION *next;  /* Next explosion on the list. */
  
} EXPLOSION;

/* Explosion data. */
#define EXPLOSION_FRAMES 4
#define EXPLOSION_RATE 50
#define EXPLOSION_EXTENTION ".png"
#define EXPLOSION_SMALL "explosion_small"
#define EXPLOSION_MEDIUM "explosion_medium"
#define EXPLOSION_BIG "explosion_big"

#endif /* _EXPLOSION_H_ */

/* Creates an explosion of a certain size and adds it to the list. */
void new_explosion( Sint32 x, Sint32 y, SIZE s );

/* Draws explosions, and removes them from the list when their 
 * animation is over. */
void draw_explosions();
