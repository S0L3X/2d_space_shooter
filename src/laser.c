#include "laser.h"
#include "ring_buffer.h"

static void update_laser( Item* laser ) {
    if ( laser->position.y < -20 ) laser->active = false;
    laser->position.y -= LASER_SPEED;
}

void draw_laser( RingBuffer* rb ) {
    int laser_width = 4;
    int laser_height = 20;

    for ( int i = rb->tail; i != rb->head; i = ( i + 1 ) % rb->number_of_items )
    {
        Item* item = &rb->items[i];
        if ( item->active ) {
            DrawRectangle( item->position.x, item->position.y, laser_width, laser_height, GOLD );
        }
    }
}

void fire_laser( RingBuffer* rb, Vector2 position ) {
    Item* laser = rb->add_item( rb );
    if ( !laser ) {
        puts( "Laser Buffer Full!" );
        return;
    }

    laser->position = position;
    laser->active = true;
    laser->update = update_laser;
}