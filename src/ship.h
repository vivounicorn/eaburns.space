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

/* Creates the ship object of the given type `t.' */
void new_ship( char *t );

/* Frees the ship. */
void free_ship();

/* Draws the ship. */
void draw_ship();

/* Move the ship in different dirrections. */
void ship_left();
void ship_right();
void ship_up();
void ship_down();

/* Make the ship's sprite the center one. */
void ship_center();

/* Makes the ship shoot. */
void ship_shoot();

/* Returns the ship's sprite. */
SPRITE* get_ship_sprite();

/* Called when the ship gets hit. */
void ship_hit();

/* Getters for the ship. */
Uint32 get_life();
Uint32 get_max_life();
