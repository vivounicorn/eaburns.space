#
# Copyright (C) 2004, 2005 Ethan A. Burns <eaburns@cisunix.unh.edu>
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later
# version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

bin_PROGRAMS=space

space_SOURCES=enemy.c explosion.c main.c planet.c score.c sdl.c \
  ship.c sprite.c stars.c config.h enemy.h explosion.h \
  planet.h score.h sdl.h ship.h side.h size.h sprite.h stars.h \
  bullet.h bullet.c ship_types.h ship_types.c xml.h xml.c \
  xml_tags.h xml_tags.c lifebar.h lifebar.c font.h font.c \
  color.h color.c data.h data.c fps.h fps.c level.h level.c \
  gameover.h gameover.c arguments.h arguments.c m_pattern.h \
  m_pattern.c bullet_types.h bullet_types.c

AM_CFLAGS=-Wall -I/usr/include/SDL
space_LDADD=-lSDL -lSDL_image -lSDL_ttf -lexpat
