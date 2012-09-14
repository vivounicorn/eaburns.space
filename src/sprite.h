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

#include "side.h"

/* Sprite's flags. */

#ifndef _SPRITE_H_
#define _SPRITE_H_

/* When set, the sprite is not allowed to move off of the screen. */
#define OFF_SCREEN_FLAG 1

typedef struct {
  Sint32 speed;  /* Movement speed (in pixels). */
  Sint32 x, y; /* Coords. */
  Uint8 frames, cur_frame; /* Number of frames, current frame number. */
  SDL_Surface **surface;  /* List of frame surfaces. */
  Uint32 frame_delay; /* Frame delay in ms. */
  Uint32 disp_time;  /* Time of last display. */
  Uint8 flags;       /* Flags are defined above. */ 
} SPRITE;

#endif /* _SPRITE_H_ */

/* Returns a new sprite.
 * x: beginning x coord of the sprite.
 * y: beginning y coord of the sprite.
 * frames: Number of frames in the sprite's animation.
 * ...: char*'s that contain paths to the sprite's frame
 *      images.
 * The last argument is a Uint32 that contains the frame_delay
 * in milliseconds. */
SPRITE *new_sprite( int x, int y, Uint8 frames, ... );

/* Returns a new sprite.
 * x: beginning x coord of the sprite.
 * y: beginning y coord of the sprite.
 * frames: Number of frames in the sprite's animation.
 * images: A char array of image paths.
 * frameRate: A Uint32 that contains the frame_delay in milliseconds. */
SPRITE *new_sprite_array( int x, int y, Uint8 frames, char** images, Uint32 frameRate );

/* Frees the sprite. */
void free_sprite( SPRITE *s );

/* Sets the sprite's speed. */
void set_speed( SPRITE *s, Sint32 speed );

/* Draws a sprite. */
void draw_sprite( SPRITE *s );

/* Set the flag to not allow the sprite off the screen. */
void no_off_screen( SPRITE *s );

/* Moves a sprite around. */
void sprite_down( SPRITE *s );
void sprite_up( SPRITE *s );
void sprite_left( SPRITE *s );
void sprite_right( SPRITE *s );

/* Returns a SIDE object of overlapping sides.  If the .none field of 
 * the SIDE object is set to a 1, then there was NO COLLISION and the
 * data in the SIDE object just contains which side of s1 s0 is on.
 * If there .none field of the SIDE object is set to a 0, then there
 * was a collision and the return value contains which sides of s0 collided
 * with s1. */
SIDE sprite_collide( SPRITE *s0, SPRITE *s1 );
