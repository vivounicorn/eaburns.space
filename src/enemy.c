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

#include <stdlib.h>
#include <string.h>

#include "enemy.h"
#include "ship.h"
#include "score.h"
#include "explosion.h"
#include "sdl.h"
#include "ship_types.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/* List of enemies. */
static ENEMY *head = NULL;

/* Number of enemies in the list. */
static Uint16 num_enemies = 0;

/* Removes the enemy from the ENEMY list and frees any
 * allocated memory associated with the enemy removed. */
static void remove_enemy( ENEMY *e );

/* Kills the enemy adding to the player's score. */
static void kill_enemy( ENEMY *e );

/* Returns a 1 if the enemy moved successfull.  If the
 * enemy goes off of the bottom of the screen then this
 * function returns a 0. */
static Uint8 move_enemy( ENEMY *e );

/* Returns the enemy at index ``index'' on the enemies list.
 * NULL is returned if the index is invalid. */
static ENEMY *get_enemy( Uint16 index );

#define ENEMY_MAX_PATH_LEN 100

void new_enemy( Sint32 x, Sint32 y, const char *t )
{
  /* Paths to directions. */
  Sint32 frames;
  Sint32 delay;
  Uint32 speed;
  
  ENEMY *e;
   
  /* Create new ENEMY and add it to the list. */
  e = (ENEMY*) malloc( sizeof(ENEMY) );

  e->flags = 0;
  e->next = head;
  head = e;

  /* Set defaults. */
  e->hp = 1;
  e->type = "no_type";
  e->move_funct = NULL;
  speed = 1;
  delay = 100;
  frames = 1;
  memset( e->move_vars, -1, NUM_MOVE_VARS );

  frames = get_num_frames( t );
  delay = get_frame_delay( t );
  speed = get_speed( t );
  e->hp = get_hp( t );
  e->type = strdup( t );
  e->move_funct = get_move_funct( t );

  /* Make the left facing sprite */
  e->left = new_sprite_array( x, y, frames, get_left( t ), delay );
  if( e->left == NULL ) {
    fprintf( stderr, "Error creating new sprite: %s.\n",
              SDL_GetError() );
    exit(1);
  }
  set_speed( e->left, speed ); 

  /* Make the left facing sprite */
  e->right = new_sprite_array( x, y, frames, get_right( t ), delay );
  if( e->right == NULL ) {
    fprintf( stderr, "Error creating new sprite: %s.\n",
              SDL_GetError() );
    exit(1);
  }
  set_speed( e->right, speed ); 

  /* Make the left facing sprite */
  e->center = new_sprite_array( x, y, frames, get_center( t ), delay );
  if( e->center == NULL ) {
    fprintf( stderr, "Error creating new sprite: %s.\n",
              SDL_GetError() );
    exit(1);
  }
  set_speed( e->center, speed ); 
  
  e->current = e->center;
  enemy_center( e );

  num_enemies++;
}

void free_enemy_list()
{
  ENEMY *p;

  for( p = head; p != NULL; p = p->next ) {
    free_sprite( p->left ); 
    free_sprite( p->right ); 
    free_sprite( p->center ); 
  }
}

void draw_enemies()
{
  Uint16 i;
  ENEMY *p;
  SIDE s;

  for( i = 0; i < num_enemies; i++ ) {

    p = get_enemy( i );

    /* Attempt to move the enemy. */
    if( move_enemy( p ) == 0 )
      continue;

    /* Do things for an active enemy. */
    if( IS_ACTIVE(p->flags) ) {
      draw_sprite( p->current );  /* Draw it. */

      /* Check for a collision with the ship. */
      s = sprite_collide( p->current, get_ship_sprite() );
      if( s.none == 0  ) {
        hit_enemy( p, 5 );
        ship_hit( s );
      }
    }
  }

}

ENEMY *check_enemy_collide( SPRITE *s )
{
  Uint16 i;
  ENEMY *p;

  for( i = 0; i < num_enemies; i++ ) {

    p = get_enemy( i );
    
    if( sprite_collide( p->current, s ).none == 0 )
      return p;

  }

  return NULL;
}

void hit_enemy( ENEMY *e, Uint32 dammage )
{
  /* Only hit an active enemy. */
  if( IS_ACTIVE( e->flags ) ) {

    if( dammage >= e->hp )
      kill_enemy( e ); 
    else 
      e->hp -= dammage;

  }
}

void enemy_center( ENEMY *e )
{
  e->center->x = e->current->x; 
  e->center->y = e->current->y; 
  e->current = e->center;
}

void enemy_left( ENEMY *e )
{
  e->left->x = e->current->x; 
  e->left->y = e->current->y; 
  e->current = e->left;
}

void enemy_right( ENEMY *e )
{
  e->right->x = e->current->x; 
  e->right->y = e->current->y; 
  e->current = e->right;
}

void move_enemy_up( ENEMY *e )
{
  enemy_center( e );
  sprite_up( e->current );  
} 

void move_enemy_down( ENEMY *e )
{
  enemy_center( e );
  sprite_down( e->current );  
} 

void move_enemy_left( ENEMY *e )
{
  enemy_left( e );
  sprite_left( e->current );  
} 

void move_enemy_right( ENEMY *e )
{
  enemy_right( e );
  sprite_right( e->current );  
} 

static void remove_enemy( ENEMY *e )
{
  ENEMY *p, *j;

  for( p = j = head; p != NULL && p != e; j = p, p = p->next );

  if( p == NULL ) { return; }
  else if ( p == head ) {
    head = head->next;

  } else {
    j->next = p->next;

  }

  free_sprite( p->center );    
  free_sprite( p->left );    
  free_sprite( p->right );    
  free( p );

  num_enemies--;
}

static void kill_enemy( ENEMY *e )
{
  player_score += get_points( e->type );

  new_explosion( e->current->x, e->current->y, BIG ); 

  remove_enemy( e );
}

static Uint8 move_enemy( ENEMY *e )
{
  /* If the enemy is on the screen, then set their active flag. */
  if( e->current->y + 
      e->current->surface[e->current->cur_frame]->h > 0 )
    e->flags |= E_FLAG_ACTIVE;  /* Set the active flag. */

  /* Check if the enemy has left the bottom of the screen. */
  if( e->current->y > (Sint32)screen_height() ) {
    remove_enemy( e );
    player_score -= get_points( e->type ); 
    return 0;
  }

  /* If the enemy is not active then they only scroll down.
   * once the enemy is active they follow their movement
   * pattern. */
  if( !IS_ACTIVE( e->flags ) )
    e->current->y += ENEMY_SCROLL_SPEED;

  else if( e->move_funct == NULL )
    move_enemy_down( e );

  else
    e->move_funct( e );

  return 1;
}

static ENEMY *get_enemy( Uint16 index )
{
  Uint16 i;
  ENEMY *p;

  if( index > num_enemies ) { return NULL; }

  for( p = head, i = 0; p != NULL && i != index; p = p->next, i++ ); 

  if( i == index && p != NULL ) { return p; }

  return NULL;
}
