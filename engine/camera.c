#include "camera.h"
#include "player.h"
#include "render.h"

void update_camera_position(Camera *camera, Player player)
{
    camera->x = (player.tx - player.ty) * TILE_WIDTH_HALF;
    camera->y = (player.tx + player.ty) * TILE_HEIGHT_HALF;
}
