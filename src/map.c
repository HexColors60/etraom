
#include <stdlib.h>

#include "etraom.h"

map_t *alloc_map( buf_t *name, int width, int height )
{
	int i, j;
	map_t *m = (map_t*) malloc( sizeof(map_t) );

	m->width = width;
	m->height = height;

	m->terrain = (tile_t***) malloc( sizeof(tile_t*) * width );
	m->memory = (tile_t***) malloc( sizeof(tile_t*) * width );

	for( i = 0; i < width; i++ )
	{
		m->terrain[i] = (tile_t**) malloc( sizeof(tile_t*) * height );
		m->memory[i] = (tile_t**) malloc( sizeof(tile_t*) * height );

		for( j = 0; j < height; j++ )
		{
			m->terrain[i][j] = NULL;
			m->memory[i][j] = NULL;
		}
	}

	clear_map( m );
	m->name = bufcpy( name );

	log_add( "[alloc_map] Allocated map (0x%08x) of width %i and height %i.\n",
		m, width, height );

	return m;
}

void free_map( map_t *m )
{
	int i;

	if( m )
	{
		if( m->terrain )
		{
			for( i = 0; i < m->width; i++ )
			{
				if( m->terrain[i] )
					free( m->terrain[i] );
			}

			free( m->terrain );
		}

		if( m->memory )
		{
			for( i = 0; i < m->width; i++ )
			{
				if( m->memory[i] )
					free( m->memory[i] );
			}

			free( m->memory );
		}

		bufdestroy( m->name );

		free( m );
		log_add( "[free_map] Freed map 0x%08x.\n", m );
	}
}

void clear_map( map_t *m )
{
	int i, j;

	for( i = 0; i < m->width; i++ )
	{
		for( j = 0; j < m->height; j++ )
		{
			m->terrain[i][j] = &tile_void;
		}
	}
}

void debug_dump_map( map_t *m )
{
	int i, j;

	log_add( "[debug_dump_map] Dumping map 0x%08x - width: %i, height: %i\n",
		m, m->width, m->height );

	for( j = 0; j < m->height; j++ )
	{
		for( i = 0; i < m->width; i++ )
		{
			if( m->terrain[i][j] )
				log_add( "%c", m->terrain[i][j]->face );
			else
				log_add( "?" );
		}
		log_add( "\n" );
	}
}

int is_legal( int x, int y )
{
	return(	( x >= 0 ) && ( y >= 0 ) &&
			( x < MAP_WIDTH ) && ( y < MAP_HEIGHT ) );
}

int is_legal_strict( int x, int y )
{
	return( ( x > 0 ) && ( y > 0 ) &&
			( x < MAP_WIDTH-1 ) && ( y < MAP_HEIGHT-1 ) );
}
