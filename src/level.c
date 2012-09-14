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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "level.h"
#include "xml.h"
#include "xml_tags.h"

void load_level( const char *file )
{
  struct stat buf;
  char *err_string;

  /* Make sure file exists. */
  if( stat( file, &buf ) == -1 ) {

    /* Print an error and exit. */
    err_string = (char*)
      malloc( sizeof(char)*(strlen("Error stating level file ") + 
              strlen(file) + 1) );
    sprintf( err_string, "Error stating level file %s", file );
    perror( err_string );

    free( err_string );

    exit( 1 );
  }
  parse_xml( file );
}
