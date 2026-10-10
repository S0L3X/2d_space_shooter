#include "meteor.h"


static void update_meteor( Item* meteor ) {
    if ( !meteor->active ) return;

    if ( meteor->position.y > WINDOW_HEIGHT ) {
        meteor->position.y = -40;
    }

    meteor->position.y += 0.5;
}

void draw_meteor( RingBuffer* rb ) {
    int meteor_width = 20;
    int meteor_height = 20;

    for ( int i = rb->tail; i != rb->head; i = ( i + 1 ) % rb->number_of_items )
    {
        Item* item = &rb->items[i];
        if ( item->active ) {
            DrawRectangle(
                item->position.x,
                item->position.y,
                meteor_width,
                meteor_height,
                MAGENTA
            );
        }
    }
}

void init_meteors( RingBuffer* rb ) {
    Item* meteor = NULL;
    Vector2 position;

    for ( int i = 0; i < rb->number_of_items; i++ )
    {
        meteor = rb->add_item( rb );
        if ( !meteor ) {
            puts( "Meteor Buffer Full!" );
            return;
        }
        position = ( Vector2 ){
            ( float ) GetRandomValue( 0, WINDOW_WIDTH ),
            ( float ) GetRandomValue( 0, WINDOW_HEIGHT )
        };

        meteor->position = position;
        meteor->active = true;
        meteor->update = update_meteor;
    }
}