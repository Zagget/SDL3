#include "Enemy.h"
#include "Random.h"

void Enemy::Update(float deltaTime, float scaledDeltaTime) {
    //directionTimer -= deltaTime;

    //// Pick new direction if timer expired
    //if (directionTimer <= 0.0f) {
    //    currentDir = Random::RangeInt(0, 4); // 0–3 = move, 4 = idle
    //    directionTimer = Random::RangeFloat(0.5f, 2.0f); // Change every 0.5–2s
    //}

    //xMove = 0;
    //yMove = 0;

    //// set direction
    //switch (currentDir) {
    //case 0: yMove = -1; break; // up
    //case 1: xMove = -1; break; // left
    //case 2: yMove = 1; break; // down
    //case 3: xMove = 1; break; // right
    //case 4: /* idle */ break;
    //}

    //// apply movement
    //SetMovement();
}