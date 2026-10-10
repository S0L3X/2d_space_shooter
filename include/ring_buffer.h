#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "settings.h"

struct Item {
    Vector2 position;
    bool active;

    void ( *update )( Item* );
};

struct RingBuffer {
    int id;
    int head;
    int tail;
    int number_of_items;
    Item* items;

    void ( *update )( RingBuffer* );
    void* ( *add_item )( RingBuffer* );
};

void rb_init( RingBuffer* rb, int id );

#endif // RING_BUFFER_H_