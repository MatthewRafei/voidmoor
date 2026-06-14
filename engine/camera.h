#ifndef CAMERA_H
#define CAMERA_H

#include "player.h"

typedef struct {
    int x;
    int y;
} Camera;

void update_camera_position(Camera *camera, Player player);

#endif //CAMERA_H
