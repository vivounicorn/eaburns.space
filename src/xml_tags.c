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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "xml_tags.h"
#include "xml.h"
#include "ship_types.h"
#include "data.h"
#include "enemy.h"
#include "m_pattern.h"
#include "bullet_types.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/* Ship data. */
SHIP_TYPE *tag_ship_type = NULL;
static Sint32 center_index = 0;
static Sint32 left_index = 0;
static Sint32 right_index = 0;

/* Level data. */
static Uint16 level_num = 0;

/* Bullet data. */
static BULLET_TYPE *tag_bullet_type = NULL;

/* The table of call back functions for tags. */
struct TAG_TYPE_TABLE tag_table[] = {
  { "ships",      SHIPS,       ships_tag_funct,      NULL },
  { "ship",       SHIP,        ship_tag_funct,       ship_tag_close_funct },
  { "speed",      SPEED,       speed_tag_funct,      NULL },
  { "frameDelay", FRAME_DELAY, frameDelay_tag_funct, NULL },
  { "points",     POINTS,      points_tag_funct,     NULL },
  { "hp",         HP,          hp_tag_funct,         NULL },
  { "frames",     FRAMES,      frames_tag_funct,     NULL },
  { "center",     CENTER,      center_tag_funct,     NULL },
  { "left",       LEFT,        left_tag_funct,       NULL },
  { "right",      RIGHT,       right_tag_funct,      NULL },
  { "level",      LEVEL,       level_tag_funct,      level_tag_close_funct },
  { "enemy",      ENEMY_TAG,   enemy_tag_funct,      NULL },
  { "movement",   MOVEMENT,    movement_tag_funct,   NULL },
  { "bullets",    BULLETS,     bullets_tag_funct,    NULL },
  { "bullet",     BULLET_TAG,  bullet_tag_funct,     bullet_tag_close_funct },
  { "bimage",     BIMAGE,      bimage_tag_funct,     NULL},
  { "bdelay",     BDELAY,      bdelay_tag_funct,     NULL},
  { "bdammage",   BDAMMAGE,    bdammage_tag_funct,   NULL},
  { NULL,           NONE,        NULL,                 NULL }
};

/* Gets the value of the attribute `attr' from the attrs list. */
static const char *get_attr( const char **attrs, char *attr );

void ships_tag_funct( const char **attrs )
{
  if( stack_top() != NONE ) {
    fprintf( stderr,
      "Error parsing XML file, ships tag must not be inside another tag.\n" );
    exit( 1 );

  } else {

    stack_push( SHIPS );
  }
}

void ship_tag_funct( const char **attrs )
{
  /* Enemy tag must be the first tag on the stack. */
  if( stack_top() != SHIPS ) {
    fprintf( stderr,
      "Error parsing XML file, ship tag must be inside an ships tag.\n" );
    exit( 1 );

  } else {
    stack_push( SHIP );
    tag_ship_type = (SHIP_TYPE*) malloc( sizeof(SHIP_TYPE) );
    tag_ship_type->name = strdup( get_attr( attrs, "name" ) );

    /* Set some defaults. */
    tag_ship_type->center_frames = NULL;
    tag_ship_type->left_frames = NULL;
    tag_ship_type->right_frames = NULL;
    tag_ship_type->num_frames = 0;
    tag_ship_type->frame_delay = 0;
    tag_ship_type->hp = 0;
    tag_ship_type->speed = 0;
    tag_ship_type->points = 0;
    tag_ship_type->move_funct = NULL;

  }
}

void speed_tag_funct( const char **attrs )
{
  if( stack_top() != SHIP ) {
    fprintf( stderr,
      "Error parsing XML file, speed tag must be inside a ship tag.\n" );
    exit( 1 );

  } else {
    assert( tag_ship_type != NULL );

    stack_push( SPEED );
    tag_ship_type->speed = atoi( get_attr( attrs, "val" ) );

  }
}

void frameDelay_tag_funct( const char **attrs )
{
  if( stack_top() != SHIP ) {
    fprintf( stderr,
      "Error parsing XML file, frameDelay tag must be inside a ship tag.\n" );
    exit( 1 );

  } else {
    assert( tag_ship_type != NULL );

    stack_push( FRAME_DELAY);
    tag_ship_type->frame_delay = atoi( get_attr( attrs, "val" ) );

  }
}

void points_tag_funct( const char **attrs )
{
  if( stack_top() != SHIP ) {
    fprintf( stderr,
      "Error parsing XML file, points tag must be inside a ship tag.\n" );
    exit( 1 );

  } else {
    assert( tag_ship_type != NULL );

    stack_push( POINTS );
    tag_ship_type->points = atoi( get_attr( attrs, "val" ) );

  }
}

void hp_tag_funct( const char **attrs )
{
  if( stack_top() != SHIP ) {
    fprintf( stderr,
      "Error parsing XML file, hp tag must be inside a ship tag.\n" );
    exit( 1 );

  } else {
    assert( tag_ship_type != NULL );

    stack_push( HP );
    tag_ship_type->hp = atoi( get_attr( attrs, "val" ) );

  }
}

void frames_tag_funct( const char **attrs )
{
  if( stack_top() != SHIP ) {
    fprintf( stderr,
      "Error parsing XML file, frames tag must be inside a ship tag.\n" );
    exit( 1 );

  } else {
    assert( tag_ship_type != NULL );

    stack_push( FRAMES );
    tag_ship_type->num_frames = atoi( get_attr( attrs, "num" ) );

    /* Allocate lists for frames. */
    tag_ship_type->center_frames =
      (char**) malloc( sizeof(char*) * tag_ship_type->num_frames );
    tag_ship_type->left_frames =
      (char**) malloc( sizeof(char*) * tag_ship_type->num_frames );
    tag_ship_type->right_frames =
      (char**) malloc( sizeof(char*) * tag_ship_type->num_frames );

  }
}

void center_tag_funct( const char **attrs )
{
  char *image;

  if( stack_top() != FRAMES ) {
    fprintf( stderr,
      "Error parsing XML file, center tag must be inside a frames tag.\n" );
    exit( 1 );

  } else if( center_index >= tag_ship_type->num_frames ) {
    fprintf( stderr, "Number of center frames exceeds number of possible frames.\n" );
    exit( 1 );

  } else {
    assert( tag_ship_type != NULL );

    stack_push( CENTER );
    image = strdup( get_attr( attrs, "image" ) );
    tag_ship_type->center_frames[center_index++] = get_data( image, DATA_IMAGES );
    free( image );
  }
}

void left_tag_funct( const char **attrs )
{
  char *image;

  if( stack_top() != FRAMES ) {
    fprintf( stderr,
      "Error parsing XML file, left tag must be inside a frames tag.\n" );
    exit( 1 );

  } else if( left_index >= tag_ship_type->num_frames ) {
    fprintf( stderr, "Number of left frames exceeds number of possible frames.\n" );
    exit( 1 );

  } else {
    assert( tag_ship_type != NULL );

    stack_push( LEFT );
    image = strdup( get_attr( attrs, "image" ) );
    tag_ship_type->left_frames[left_index++] = get_data( image, DATA_IMAGES );
    free( image );

  }
}

void right_tag_funct( const char **attrs )
{
  char *image;

  if( stack_top() != FRAMES ) {
    fprintf( stderr,
      "Error parsing XML file, right tag must be inside a frames tag.\n" );
    exit( 1 );

  } else if( right_index >= tag_ship_type->num_frames ) {
    fprintf( stderr, "Number of right frames exceeds number of possible frames.\n" );
    exit( 1 );

  } else {
    assert( tag_ship_type != NULL );

    stack_push( RIGHT );
    image = strdup( get_attr( attrs, "image" ) );
    tag_ship_type->right_frames[right_index++] = get_data( image, DATA_IMAGES );
    free( image );
  }
}

void level_tag_funct( const char **attrs )
{
  if( stack_top() != NONE ) {
    fprintf( stderr,
      "Error parsing XML file, level tag must not be inside another tag.\n" );
    exit( 1 );

  } else {

    stack_push( LEVEL );
    level_num = atoi(get_attr( attrs, "num"));
  }
}

void enemy_tag_funct( const char **attrs )
{
  Sint32 x, y;
  const char *type;

  if( stack_top() != LEVEL ) {
    fprintf( stderr,
      "Error parsing XML file, enemy tag must be inside a level tag.\n" );
    exit( 1 );

  } else {

    x = atoi( get_attr( attrs, "x") );
    y = atoi( get_attr( attrs, "y") );
    type = get_attr( attrs, "type" );

    new_enemy( x, y, type );
    stack_push( ENEMY_TAG );
  }
}

void movement_tag_funct( const char **attrs )
{
  if( stack_top() != SHIP ) {
    fprintf( stderr,
      "Error parsing XML file, enemy tag must be inside a level tag.\n" );
    exit( 1 );

  } else {

    tag_ship_type->move_funct = get_movement_pattern( get_attr( attrs, "pattern" ) );

    stack_push( MOVEMENT );
  }
}

void bullets_tag_funct( const char **attrs )
{
  if( stack_top() != NONE ) {
    fprintf( stderr,
      "Error parsing XML file, bullets tag must not be inside any other tag.\n" );
    exit( 1 );

  } else {

    stack_push( BULLETS );

  }
}

void bullet_tag_funct( const char **attrs )
{
  if( stack_top() != BULLETS ) {
    fprintf( stderr,
      "Error parsing XML file, bullet tag must be inside a bullets tag.\n" );
    exit( 1 );

  } else {

    assert( tag_bullet_type == NULL );

    tag_bullet_type = (BULLET_TYPE*) malloc( sizeof( BULLET_TYPE ) );

    tag_bullet_type->name = strdup( get_attr( attrs, "name" ) );

    stack_push( BULLET_TAG );
  }
}

void bimage_tag_funct( const char **attrs )
{
  char *image;

  if( stack_top() != BULLET_TAG ) {
    fprintf( stderr,
      "Error parsing XML file, bimage tag must be inside a bullet tag .\n" );
    exit( 1 );

  } else {

    assert( tag_bullet_type != NULL );

    stack_push( BIMAGE );

    image = strdup( get_attr( attrs, "image" ) );
    tag_bullet_type->image = get_data( image, DATA_IMAGES );

    free( image );
  }
}

void bdelay_tag_funct( const char **attrs )
{

  if( stack_top() != BULLET_TAG ) {
    fprintf( stderr,
      "Error parsing XML file, bdelay tag must be inside a bullet tag .\n" );
    exit( 1 );

  } else {

    assert( tag_bullet_type != NULL );

    stack_push( BDELAY );

    tag_bullet_type->delay = atoi( get_attr( attrs, "val" ) );
  }
}

void bdammage_tag_funct( const char **attrs )
{
  if( stack_top() != BULLET_TAG ) {
    fprintf( stderr,
      "Error parsing XML file, bdammage tag must be inside a bullet tag .\n" );
    exit( 1 );

  } else {

    assert( tag_bullet_type != NULL );

    stack_push( BDAMMAGE );

    tag_bullet_type->dammage = atoi( get_attr( attrs, "val" ) );
  }
}

/*
 * tag_close functions.
 */

void ship_tag_close_funct()
{
  add_ship_type( tag_ship_type );
  center_index = 0;
  left_index = 0;
  right_index = 0;
}

void level_tag_close_funct()
{
  level_num = 0;
}

void bullet_tag_close_funct()
{
  assert( tag_bullet_type != NULL );
  add_bullet_type( tag_bullet_type );
  tag_bullet_type = NULL;
}

static const char *get_attr( const char **attrs, char *attr )
{
  Sint32 i;

  for( i = 0; attrs[i]; i += 2 )
    if( strcmp( attrs[i], attr ) == 0 ) { return attrs[i+1]; }

  return NULL;
}
