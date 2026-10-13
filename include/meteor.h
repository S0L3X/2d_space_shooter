#ifndef METEOR_H_
#define METEOR_H_

#include "settings.h"
#include "ring_buffer.h"

void draw_meteor( RingBuffer* rb );
void init_meteors( RingBuffer* rb, Texture2D* texture );


#endif // METEOR_H_