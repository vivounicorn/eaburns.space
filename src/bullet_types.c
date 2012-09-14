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
#include <stdlib.h>
#include <string.h>

#include "bullet_types.h"
#include "xml.h"

/* Linked list of bullet types. */
static BULLET_TYPE *head = NULL;

/* Returns a pointer to the BULLET_TYPE with the given name. */
static BULLET_TYPE *get_bullet_type( const char *t );

void get_bullets( const char *file )
{
  parse_xml( file );
}


void add_bullet_type( BULLET_TYPE *t )
{
  t->next = head;
  head = t; 
}

void free_bullet_types()
{
  BULLET_TYPE *p;
  
  while( head != NULL ) {
    p = head;
    head = head->next;
    free( p );
  }
}

char *get_bullet_image( const char *t )
{
  return get_bullet_type( t )->image;
}

Uint8 get_bullet_delay( const char *t )
{
  return get_bullet_type( t )->delay;
}

Uint32 get_bullet_dammage( const char *t )
{
  return get_bullet_type( t )->dammage;
}

BULLET_TYPE *get_bullet_type( const char *t )
{
  BULLET_TYPE *p;

  /* Find the ship type on the list. */  
  p = head;
  while( p != NULL && strcmp(p->name, t) != 0 )
    p = p->next;

  if( p != NULL && strcmp(p->name, t) == 0 )
    return p;

  fprintf( stderr, "Bullet type %s not found.\n", t );
  exit( 1 );
}
