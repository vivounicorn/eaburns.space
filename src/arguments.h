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

/* Verbosity level. */
extern Uint8 verbosity;

/* User specified level file. */
extern char *user_level;

#define V_PRINT( x, y... ) \
  do{ \
    if( verbosity >= x ) { \
      fprintf( stderr, y ); \
    } \
  } while( 0 /* CONST COND */ )

/* Parse the commandline arguments and set some globals. */ 
void parse_args( int argc, char **argv );
