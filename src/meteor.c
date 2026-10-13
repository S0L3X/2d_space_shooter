#include "meteor.h"


static void update_meteor( Sprite* meteor, float dt ) {
    if ( !meteor->active ) return;

    if ( meteor->position.y > WINDOW_HEIGHT + meteor->size.y ) {
        meteor->position.y = -meteor->size.y * 2;
    }
    if ( meteor->position.x > WINDOW_WIDTH + meteor->size.x ) {
        meteor->position.x = -meteor->size.x * 2;
    }
    else if ( meteor->position.x < -meteor->size.x * 2 ) {
        meteor->position.x = WINDOW_WIDTH + ( meteor->size.x * 2 );
    }

    meteor->position.x += meteor->direction.x * meteor->speed * dt;
    meteor->position.y += meteor->direction.y * meteor->speed * dt;
}

static void draw_texture( Sprite* s ) {
    Rectangle src_rec = { 0, 0, s->texture->width, s->texture->height };
    Rectangle dst_rec = { s->position.x, s->position.y, s->size.x, s->size.y };
    Vector2 origin = { ( int ) s->size.x / 2, ( int ) s->size.y / 2 };

    DrawTexturePro( *s->texture, src_rec, dst_rec, origin, 0.0f, WHITE );
}

void draw_meteor( RingBuffer* rb ) {
    for ( int i = rb->tail; i != rb->head; i = ( i + 1 ) % rb->count )
    {
        Sprite* meteor = &rb->items[i];

        if ( meteor->active )
            draw_texture( meteor );

    }
}

static void meteor_ctor( Sprite* meteor, Texture2D* texture ) {
    Vector2 position = ( Vector2 ){
                GetRandomValue( 0, WINDOW_WIDTH ),
                GetRandomValue( -150, -50 )
    };
    int size = GetRandomValue( 10, texture->width );
    int dir = GetRandomValue( -5, 5 );
    float dir_x = ( float ) dir * 0.1f;
    float speed = GetRandomValue( 300, 400 );

    meteor->texture = texture;
    meteor->position = position;
    meteor->size = ( Vector2 ){ size, size };
    meteor->direction = ( Vector2 ){ dir_x, 1.0f };
    meteor->speed = speed;
    meteor->active = true;
    meteor->update = update_meteor;
}

void init_meteors( RingBuffer* rb, Texture2D* texture ) {
    Sprite* meteor = NULL;

    for ( int i = 0; i < rb->count; i++ )
    {
        meteor = rb->add_item( rb );
        if ( !meteor ) {
            puts( "Meteor Buffer Full!" );
            return;
        }

        meteor_ctor( meteor, texture );
    }
}

void spawn_meteor(RingBuffer* rb) {
    puts("Spawn Meteor");
    UNUSED(rb);
}