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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "arguments.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

static char *prefix = NULL;

/* Returns a 1 if the path is statable. */
static Uint8 check_path( const char *path );

/* An exit hook that frees the prefix variable. */
static void clean_prefix();

char *get_data( const char* file, const char* dir )
{
  char *retval;

  /* Find the base data dir. */
  if( prefix == NULL ) {
    if( check_path( DATA ) == 1 ) {
      prefix = (char*)malloc( sizeof(char) * (strlen(DATA)+1) );
      sprintf( prefix, "%s", DATA );

      atexit(clean_prefix);

    } else if( check_path( "../data" ) == 1 ) {
      /* Print an error message. */
      V_PRINT( 2, "Unable to find data at [%s].\n", DATA );

      prefix = (char*)malloc( sizeof(char) * (strlen("../data")+1) );
      strcpy( prefix, "../data" );
      V_PRINT( 1, "prefix: [%s].\n", prefix );

      atexit(clean_prefix);

    } else {
      perror( "Unable to find data at ../data/" );
      exit( 1 );
    }
  }

  //fprintf( stderr, "prefix: [%s].\n", prefix );
  retval = (char*)malloc( sizeof(char)*(strlen(prefix) + 
    strlen(file) + strlen(dir) + 3) );

  sprintf( retval, "%s/%s/%s", prefix, dir, file );

  return retval;
}

static Uint8 check_path( const char *path )
{
  struct stat stat_buff;

  if( stat( path, &stat_buff ) != 0 )
    return 0;
  
  if( !S_ISDIR(stat_buff.st_mode) )
    return 0;

  return 1; 
}

static void clean_prefix()
{
  free( prefix );
}
