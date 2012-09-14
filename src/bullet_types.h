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

#ifndef _BULLET_TYPE_H_
#define _BULLET_TYPE_H_

/* List of types of bullets loaded from XML. */
typedef struct _BULLET_TYPE {

  char *name;
  char *image;
  Uint8 delay;
  Uint32 dammage;
 
  struct _BULLET_TYPE *next; 
  
} BULLET_TYPE;

#endif /* _BULLET_TYPE_H_ */

/* Loads bullets from an XML file. */
void get_bullets( const char *file );

/* Adds a BULLET_TYPE to the list. */
void add_bullet_type( BULLET_TYPE *t );

/* Frees the list of bullets. */
void free_bullet_types();

/* Gets a bullet type.s fields: */
char *get_bullet_image( const char *t );
Uint8 get_bullet_delay( const char *t );
Uint32 get_bullet_dammage( const char *t );
