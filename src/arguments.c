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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "arguments.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/* Verbosity level. */
Uint8 verbosity = 0;

/* User specified level. */
char *user_level = NULL;

/* Displays help test. */
static void print_help( const char *prog );

/* Displays version info. */
static void print_version();

/* Return values for long options. */
#define ARG_VERBOSITY 133
#define ARG_VERBOSE 'v'
#define ARG_VERSION 'V'
#define ARG_HELP 'h'
#define ARG_LEVEL 'L'

void parse_args( int argc, char **argv )
{
  Sint32 c;
  Sint32 opt_index;

  /* Long options list. */
  static struct option long_opts[] = {

    {"help",       0,  0,  ARG_HELP},
    {"verbosity",  1,  0,  ARG_VERBOSITY},
    {"version",    0,  0,  ARG_VERSION}, 
    {"level",      1,  0,  ARG_LEVEL},

    { 0, 0, 0, 0 }
  };

  while( 1 /* CONST COND */ ) {

    c = getopt_long( argc, argv, "hv", long_opts, &opt_index );

    if( c == -1 ) { break; }

    switch( c ) {
      case ARG_HELP: print_help( argv[0] ); break;
      case ARG_VERBOSE: verbosity++; break; 
      case ARG_VERBOSITY: verbosity = atoi( optarg ); break;
      case ARG_VERSION: print_version(); break;

      /* This needs to be freed remember!!!!. */
      case ARG_LEVEL: user_level = strdup( optarg ); break;

    };
  }

  V_PRINT( 1, "Verbosity level: %d\n", verbosity );
  
}

static void print_help( const char *prog )
{
  printf( "Useage:\n %s [-hv] [--help] [--verbosity=<val>]\n", prog ); 
  exit( 0 );
}

static void print_version()
{
  printf( "%s version %s by Ethan Burns.\n", PACKAGE, VERSION );
  exit( 0 );
}
