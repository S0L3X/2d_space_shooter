#include "ring_buffer.h"
#include "settings.h"

static void update_items( RingBuffer* rb ) {
    for ( int i = rb->tail; i != rb->head; i = ( i + 1 ) % rb->number_of_items )
    {
        Item* item = &rb->items[i];
        if ( item->active ) item->update( item );
    }
}

static void rb_update( RingBuffer* rb ) {
    update_items( rb );

    while (
        ( rb->tail != rb->head ) && !rb->items[rb->tail].active
        ) {
        rb->tail = ( rb->tail + 1 ) % rb->number_of_items;
    }

    // Debug
    if ( rb->id == -1 ) printf( "tail: %d\thead: %d\n", rb->tail, rb->head );
}

static void* rb_add_item( RingBuffer* rb ) {
    void* item = NULL;

    if ( ( ( rb->head + 1 ) % rb->number_of_items ) != rb->tail ) {
        item = &rb->items[rb->head];
        rb->head = ( rb->head + 1 ) % rb->number_of_items;
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
    Item* items = malloc( ( max_num + 1 ) * sizeof( Item ) );

    rb->id = id;
    rb->head = 0;
    rb->tail = 0;
    rb->number_of_items = max_num + 1;
    rb->items = items;

    rb->update = rb_update;
    rb->add_item = rb_add_item;
}