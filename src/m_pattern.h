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

#ifndef _M_PATTERN_H_
#define _M_PATTERN_H_

typedef void MOVEMENT_PATTERN( void * );

typedef struct {

  /* Name of this movement pattern. */
  const char *name;

  /* The callback function. */
  MOVEMENT_PATTERN *funct;
  
} M_TABLE_ELEM;

#endif /* _M_PATTERN_H_ */

/* Table of movement patterns and their names. */
extern M_TABLE_ELEM m_table[];

MOVEMENT_PATTERN *get_movement_pattern( const char *name );

/* Enemy bears right once they are active on the screen. */
void zig_right_m_pattern( void *_e );

/* Enemy bears left once they are active on the screen. */
void zag_left_m_pattern( void *_e );
