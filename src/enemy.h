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
#include "m_pattern.h"

/* Number of variables to be used by the movement functions to store
 * movement specific data in an enemy. */
#define NUM_MOVE_VARS 1

/* This flag is set in an enemy's flag field if the
 * enemy is active.  Activity of an enemy means that they
 * are displayed on the screen. */
#define E_FLAG_ACTIVE 1
#define IS_ACTIVE( x ) ((x & E_FLAG_ACTIVE) != 0)

#ifndef _ENEMY_H_
#define _ENEMY_H_

/* Enemy linked list element */
typedef struct _ENEMY {

  /* Directions for the enemy sprites. */
  SPRITE *center;
  SPRITE *left;
  SPRITE *right; 
  
  SPRITE *current;      /* The current direction of the enemy. */  
  Uint32 hp;            /* Hit points. */
  Uint8 flags;          /* Enemy flags. */
  char *type;           /* The type of this enemy. */ 

  /* The movement callback function for this enemy. */
  MOVEMENT_PATTERN *move_funct;

  /* Movement function variables spacific to each enemy.
   * These variables can be used how ever they are needed by
   * the enemy's movement function.  These variables are guarenteed
   * to be initialized to -1. */ 
  Sint32 move_vars[NUM_MOVE_VARS];

  struct _ENEMY *next;  /* Next enemy on the list. */

} ENEMY;

/* Maximum number of frames that an enemy can have. */
#define MAX_FRAMES 5

/* Speed that an enemy scrolls onto the active screen.
 * in pixels. */
#define ENEMY_SCROLL_SPEED 2

#endif /* _ENEMY_H_ */

/* Creates a new enemy and adds them to the end of the list. */
void new_enemy( Sint32 x, Sint32 y, const char *t );

/* Frees all the remaining enemies on the list. */
void free_enemy_list();

/* Draws all the enemies on the list. */
void draw_enemies();

/* Returns NULL if there are not collisions.  If 
 * there is a collision then the enemy that the collision
 * took place with is retuned. */
ENEMY *check_enemy_collide( SPRITE *s );

/* Subtracts from an enemy's life and removes them if needed 
 * aadding appropriate ammount to the player's score. */
void hit_enemy( ENEMY *e, Uint32 dammage );

/* Makes the enemy use the center image, left image, or right image. */
void enemy_center( ENEMY *e );
void enemy_left( ENEMY *e );
void enemy_right( ENEMY *e );

/* Moves the enemy in that direction. */
void move_enemy_up( ENEMY *e );
void move_enemy_down( ENEMY *e );
void move_enemy_left( ENEMY *e );
void move_enemy_right( ENEMY *e );
