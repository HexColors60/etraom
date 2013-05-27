
#include "etraom.h"

list_t *entity_list = NULL;

entity_t *alloc_entity( buf_t *name )
{
	entity_t *e = malloc( sizeof(entity_t) );

	e->name = bufcpy( name );
	e->face = 'z';
	e->color[0] = e->color[1] = e->color[2] = 255;
	e->flags = 0;

	log_add( "[alloc_entity] Allocated entity 0x%08x('%s').\n", e,
		e->name->data );

	return e;
}

void free_entity( entity_t *e )
{
	if( e )
	{
		bufdestroy( e->name );
		free( e );
		log_add( "[free_entity] Freed entity 0x%08x.\n", e );
	}
}

void free_entities( void )
{
	list_element *e = entity_list->head;

	while( e )
	{
		free_entity( (entity_t*)e->data );
		e = e->next;
	}
}

/* entity_act should return 1 if the action is successful, otherwise 0 */
int entity_act( entity_t *e )
{
	int key, mod, quit;

	log_add( "[entity_act] Act: 0x%08x('%s').\n", e, e->name->data );

	if( e->flags & ENTITYFLAG_PLAYERCONTROL )
	{
		wait_key( &key, &mod, &quit );
		if( quit )
			running = 0;

		handle_key( key, mod );
	}
	else
	{
		/* TODO */
	}

	return 1;
}

/* entity_move_rel should return 1 if the action is successful, otherwise 0 */
int entity_move_rel( entity_t *e, int dx, int dy )
{
	if( 	( is_legal( e->map, e->x+dx, e->y+dy ) ) &&
			!( e->map->terrain[e->x+dx][e->y+dy]->flags & TILEFLAG_SOLID ) )
	{
		e->x += dx;
		e->y += dy;

		return 1;
	}
	else
	{
		return 0;
	}
}