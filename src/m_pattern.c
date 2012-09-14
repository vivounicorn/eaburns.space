#include <SDL/SDL.h>
#include <string.h>

#include "m_pattern.h"
#include "enemy.h"

M_TABLE_ELEM m_table[] = {

  { "none",       NULL },
  { "zig_right",  zig_right_m_pattern },
  { "zag_left",   zag_left_m_pattern },

  { NULL, NULL }
};

MOVEMENT_PATTERN *get_movement_pattern( const char *name )
{
  Sint32 i;
  
  for( i = 0; m_table[i].name != NULL; i++ ) {
    if( strcmp( name, m_table[i].name ) == 0 ) 
      return m_table[i].funct;
  }


  fprintf( stderr, "Returning NULL in get_movement_pattern for [%s].\n", name );
  return NULL;
}

#define ZIG_ZAG_FLAG 0

void zig_right_m_pattern( void *_e )
{
  ENEMY *e = (ENEMY*)_e;

  move_enemy_down( e );

  if( e->move_vars[ZIG_ZAG_FLAG] == 1 && IS_ACTIVE( e->flags ) ) {
    move_enemy_right( e );
    enemy_center( e );
    e->move_vars[ZIG_ZAG_FLAG] = 0;

  } else
    e->move_vars[ZIG_ZAG_FLAG] = 1;

  enemy_right( e );
}

void zag_left_m_pattern( void *_e )
{
  ENEMY *e = (ENEMY*)_e;

  move_enemy_down( e );
  
  if( e->move_vars[ZIG_ZAG_FLAG] == 1 && IS_ACTIVE( e->flags ) ) {
    move_enemy_left( e );
    e->move_vars[ZIG_ZAG_FLAG] = 0;

  } else
    e->move_vars[ZIG_ZAG_FLAG] = 1;

  enemy_left( e );
}
