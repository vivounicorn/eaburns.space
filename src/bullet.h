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

#ifndef _BULLET_H_
#define _BULLET_H_

/* List of active bullets. */
typedef struct _BULLET {
  SPRITE *sprite;
  Uint8 delay;
  Uint32 dammage;
  struct _BULLET *next; 
} BULLET;

#endif /* BULLET_H_ */

#define BULLET_1 "bullet1.png"
#define MAX_BULLETS 20 /* Maximum number of bullets. */
#define SHOOT_DELAY 100 /* This should be bullet spacific... when
                         * there is multiple types of bullets. */

/* Creates a new bullet of type t, and adds it to the list. */
void new_bullet( char *t );

/* Draws the bullets. */
void draw_bullets();

/* Deletes a bullet from the list. */
void delete_bullet( BULLET *b );
