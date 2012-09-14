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

#ifndef _XML_H_
#define _XML_H_

#include "xml_tags.h"

/* Stack for parsing XML tag stacks. */
typedef struct _STACK {

  TAG_TYPE info;

  struct _STACK *next;

} STACK;

#endif /* _XML_H_ */

/* Returns top of stack. */
TAG_TYPE stack_top();

/* Pushes `t' onto the stack. */
void stack_push( TAG_TYPE t );

/* Pops the top value off the stack and returns it. */
TAG_TYPE stack_pop();

/* Call backs for XML parsing. */
void xml_start( void *data, const char *tag, const char **attr );
void xml_end( void *data, const char *tag );

/* Parses an xml file. */
void parse_xml( const char *file );
