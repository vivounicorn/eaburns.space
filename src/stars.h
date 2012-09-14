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

#include "size.h"

#ifndef _STAR_H_
#define _STAR_H_

typedef struct {
  SIZE size;  /* The size of the star. */
  Uint32 x, y;    /* The coordinates of the star. */
  Uint32 speed;    /* The star's speed. */
} STAR;

#endif /* _STAR_H_ */

/* Creates stars placed around the screen. */
void create_stars();

/* Displays stars MOVING down the screen in the background. */
void draw_stars();
