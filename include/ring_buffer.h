#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "settings.h"
#include "sprite.h"

// struct Item {
//     Vector2 position;
//     bool active;

//     void ( *update )( Item* );
// };

struct RingBuffer {
    int id;
    int head;
    int tail;
    int count;
    Sprite* items;

    void ( *update )( RingBuffer*, float );
    void* ( *add_item )( RingBuffer* );
};

void rb_init( RingBuffer* rb, int id );

#endif // RING_BUFFER_H_