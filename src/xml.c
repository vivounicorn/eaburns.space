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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <expat.h>
#include <string.h>

#include "xml.h"
#include "xml_tags.h"
#include "arguments.h"

static STACK *stack_head = NULL;

/* Get top value of the stack. */
TAG_TYPE stack_top() 
{ 
  if( stack_head == NULL ) 
    return NONE;

  return stack_head->info; 
}

/* Push a value on the stack. */
void stack_push( TAG_TYPE t )
{
  STACK *p;
  p = (STACK*) malloc( sizeof(STACK) );
  p->info = t;
  p->next = stack_head;
  stack_head = p; 
}

/* Pop a value off the top of the stack and return it. */
TAG_TYPE stack_pop()
{
  TAG_TYPE retval = NONE;
  STACK *p;

  if( stack_head != NULL ) { 
    retval = stack_head->info;
    p = stack_head;
    stack_head = stack_head->next;
    free( p ); 
  }

  return retval;
}

/*
 * XML Call back functions.
 */
void xml_start( void *data, const char *tag, const char **attr )
{
  Sint32 i;

  V_PRINT( 3, "tag: %s ", tag ); 

  for( i = 0; attr[i]; i += 2 )
    V_PRINT( 3, "%s=%s ", attr[i], attr[i+1] );

  V_PRINT( 3, "\n" );

  for( i = 0; tag_table[i].name != NULL; i++ ) {
    if( strcmp( tag_table[i].name, tag ) == 0 ) {
      tag_table[i].funct( attr );
      break;
    }
  }
}

void xml_end( void *data, const char *tag )
{
  Sint32 i;

  for( i = 0; tag_table[i].name != NULL; i++ ) {
    if( strcmp( tag_table[i].name, tag ) == 0 && 
        tag_table[i].close_funct != NULL ) {
      tag_table[i].close_funct();
      break;
    }
  }

  stack_pop();
}

void parse_xml( const char *file )
{
  char *buff;
  Sint32 buff_len;
  Sint32 done = 0;
  FILE *f;
  XML_Parser p; 
  struct stat s;

  if( stat( file, &s ) == -1 ) {
    buff = (char*)
      malloc( sizeof(char) * 
      (strlen(file)+strlen("Stat failed on ") + 1) );
    sprintf( buff, "Stat failed on %s", file );
    perror( buff );
    free( buff );
    exit( 1 );
  }

  /* Allocate a buffer the length of the file. */
  buff_len = s.st_size;
  buff = (char*) malloc( sizeof(char) * buff_len );

  /* Open and try to read from ``file.'' */
  f = fopen( file, "r" );
  if( fread( buff, 1, buff_len, f ) != buff_len ) {
    fprintf( stderr, "Unable to read all of file: %s.\n", file );    
    free( buff );
    exit( 1 );
  }
  fclose( f );

  /* Create an XML parser and set it's call back functions. */
  p = XML_ParserCreate(NULL);
  if( p == NULL ) {
    fprintf( stderr, "Couldn't allocate memory for XML parser.\n" );
    free( buff );
    exit( 1 );
  }

  XML_SetElementHandler( p, xml_start, xml_end );

  /* Parse the XML file. */
  if( XML_Parse( p, buff, buff_len, done ) == 0 ) {
    fprintf( stderr, "Parse error at line %d:\n%s\n",
      XML_GetCurrentLineNumber( p ), 
      XML_ErrorString( XML_GetErrorCode(p) ));
    free( buff );
    exit( 1 );
  } 

  free( buff );
}
