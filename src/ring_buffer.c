#include "ring_buffer.h"
#include "settings.h"

static void update_items( RingBuffer* rb, float dt ) {
    for ( int i = rb->tail; i != rb->head; i = ( i + 1 ) % rb->count )
    {
        Sprite* item = &rb->items[i];
        if ( item->active ) item->update( item, dt );
    }
}

static void rb_update( RingBuffer* rb, float dt ) {
    update_items( rb, dt );
    
    while (
        ( rb->tail != rb->head ) && !rb->items[rb->tail].active
        ) {
        rb->tail = ( rb->tail + 1 ) % rb->count;
    }

    // Debug
    if ( rb->id == -1 ) printf( "tail: %d\thead: %d\n", rb->tail, rb->head );
}

static void* rb_add_item( RingBuffer* rb ) {
    void* item = NULL;

    if ( ( ( rb->head + 1 ) % rb->count ) != rb->tail ) {
        item = &rb->items[rb->head];
        rb->head = ( rb->head + 1 ) % rb->count;
    }

    return item;
}

void rb_init( RingBuffer* rb, int id ) {
    int max_num;

    switch ( id ) {
    case LASER:
        max_num = MAX_LASERS;
        break;

    case METEOR:
        max_num = MAX_METEORS;
        break;

    default:
        break;
    }
    // Ring Buffer is always full at 1 less than max_num for some reason i.e. max_num 10 only adds 9 items.
    Sprite* items = malloc( ( max_num + 1 ) * sizeof( Sprite ) );
    if (!items) exit(EXIT_FAILURE);

    rb->id = id;
    rb->head = 0;
    rb->tail = 0;
    rb->count = max_num + 1;
    rb->items = items;

    rb->update = rb_update;
    rb->add_item = rb_add_item;
}