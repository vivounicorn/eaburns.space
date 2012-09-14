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

#ifndef _XML_TAGS_H_
#define _XML_TAGS_H_

#include "ship_types.h"

typedef enum {
  NONE, SHIPS, SHIP, SPEED, FRAME_DELAY,
  POINTS, HP, FRAMES, CENTER, LEFT, RIGHT,
  MOVEMENT, LEVEL, ENEMY_TAG, BULLET_TAG,
  BULLETS, BIMAGE, BDELAY, BDAMMAGE
} TAG_TYPE;


/* Elements for a table of call back functions for tag types. */
struct TAG_TYPE_TABLE {
  char *name;                   /* The tag's name. (The text of the tag). */
  TAG_TYPE type;                /* Tag type. */
  void(*funct)(const char **attrs);   /* Call back function. */
  void(*close_funct)();         /* Call back funct for a closing tag. */
};

extern struct TAG_TYPE_TABLE tag_table[];

extern SHIP_TYPE *tag_ship_type;

/* Call back functions for xml close tags. */

/* Ship stuff. */
void ships_tag_funct( const char **attrs );
void ship_tag_funct( const char **attrs );
void speed_tag_funct( const char **attrs );
void frameDelay_tag_funct( const char **attrs );
void points_tag_funct( const char **attrs );
void hp_tag_funct( const char **attrs );
void frames_tag_funct( const char **attrs );
void center_tag_funct( const char **attrs );
void left_tag_funct( const char **attrs );
void right_tag_funct( const char **attrs );
void movement_tag_funct( const char **attrs );

/* Level stuff. */
void level_tag_funct( const char **attrs );
void enemy_tag_funct( const char **attrs );

/* Bullet stuff. */
void bullets_tag_funct( const char **attrs );
void bullet_tag_funct( const char **attrs );
void bimage_tag_funct( const char **attrs );
void bdelay_tag_funct( const char **attrs );
void bdammage_tag_funct( const char **attrs );

/* Call back function for xml close tags. */
void ship_tag_close_funct();
void level_tag_close_funct();
void bullet_tag_close_funct();

#endif /* _XML_TAGS_H_ */
