#include "Level1.h"

#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMYCOUNT 4

unsigned int level1_data[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    17, 65, 17, 17, 17, 17, 17, 19, 17, 17, 17, 17, 64, 17,
    52, 81, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 80, 52,
    36, 50, 50, 50, 50, 96, 97, 98, 99, 50, 50, 50, 50, 36,
    52, 50, 50, 50, 50, 112, 113, 114, 115, 50, 50, 50, 50, 52,
    36, 50, 50, 50, 50, 128, 129, 130, 131, 50, 50, 50, 50, 36,
    52, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 52,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17
    // 36, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 36
};

void Level1::Initialize() {
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("dungeon-v1-tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 16, 16);

    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(4, -3.5, 0);
    state.player->movement = glm::vec3(0);
//    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.0f;
//    state.player->textureID = Util::LoadTexture("george_0.png");
    state.player->textureID = Util::LoadTexture("player.png");
    
//    state.player->animRight = new int[4] {3, 7, 11, 15};
//    state.player->animLeft = new int[4] {1, 5, 9, 13};
//    state.player->animUp = new int[4] {2, 6, 10, 14};
//    state.player->animDown = new int[4] {0, 4, 8, 12};
    
    state.player->animRight = new int[4] {39, 40, 41, 42};
    state.player->animLeft = new int[4] {13, 14, 15, 16};
    state.player->animUp = new int[4] {52, 53, 54, 55};
    state.player->animDown = new int[4] {26, 27, 28, 29};
    
    state.player->animActionRight = new int[4] {195, 198, 199, 200};
    state.player->animActionLeft = new int[4] {169, 172, 173, 174};
    state.player->animActionUp = new int[4] {160, 161, 160, 161};
    state.player->animActionDown = new int[4] {183, 185, 186, 187};
    
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 13;
    state.player->animRows = 21;
    
    state.player->height = 0.8f;
    state.player->width = 0.8f;
    
    /*
    state.player->dashPower = 10.0f;
    
    state.dash = new Entity();
    state.dash->entityType = DASH;
    state.dash->position = glm::vec3(5, -3, 0);
    state.dash->movement = glm::vec3(0);
    state.dash->speed = 2.0f;
    state.dash->textureID = Util::LoadTexture("player.png");

    state.dash->animRight = new int[4] {39, 40, 41, 42};
    state.dash->animLeft = new int[4] {13, 14, 15, 16};
    state.dash->animUp = new int[4] {52, 53, 54, 55};
    state.dash->animDown = new int[4] {26, 27, 28, 29};

    state.dash->animIndices = state.player->animRight;
    state.dash->animFrames = 4;
    state.dash->animIndex = 0;
    state.dash->animTime = 0;
    state.dash->animCols = 13;
    state.dash->animRows = 21;

    state.dash->height = 0.8f;
    state.dash->width = 0.8f;
    state.dash->timeLeft = 0.25f;
    state.dash->isActive = false;
    */
    
    state.enemies = new Entity[LEVEL1_ENEMYCOUNT];
    GLuint enemyTextureID = Util::LoadTexture("orc.png");
    
    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
        state.enemies[i].animRight = new int[4] {143, 144, 145, 146};
        state.enemies[i].animLeft = new int[4] {117, 118, 119, 120};
        state.enemies[i].animUp = new int[4] {104, 105, 106, 107};
        state.enemies[i].animDown = new int[4] {130, 131, 132, 133};
        
        state.enemies[i].animIndices = state.enemies[i].animLeft;
        state.enemies[i].animFrames = 4;
        state.enemies[i].animIndex = 0;
        state.enemies[i].animTime = 0;
        state.enemies[i].animCols = 13;
        state.enemies[i].animRows = 21;
    }
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(13, -2, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = PATROL_X;

    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(1, -5, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = PATROL_X;
    state.enemies[1].animIndices = state.enemies[1].animRight;
    
    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(1, -2, 0);
    state.enemies[2].speed = 1;
    state.enemies[2].aiType = WAITANDGO;
    state.enemies[2].aiState = PATROL_Y;
    state.enemies[2].animIndices = state.enemies[2].animDown;
    
    state.enemies[3].entityType = ENEMY;
    state.enemies[3].textureID = enemyTextureID;
    state.enemies[3].position = glm::vec3(11, -5, 0);
    state.enemies[3].speed = 1;
    state.enemies[3].aiType = WAITANDGO;
    state.enemies[3].aiState = PATROL_Y;
    state.enemies[3].animIndices = state.enemies[3].animUp;
}

void Level1::Update(float deltaTime) {
    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    }
    
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    
    // If all enemies are dead and player is alive, proceed to next scene
    bool enemiesAlive = false;
    for (int i = 0; i < LEVEL1_ENEMYCOUNT; i++) {
        if (!state.enemies[i].dead) enemiesAlive = true;
    }
    
    if (!enemiesAlive && !state.player->dead) state.nextScene = 2;
}

void Level1::Render(ShaderProgram *program) {
    state.map->Render(program);
    
    for (int i = 0; i  < LEVEL1_ENEMYCOUNT; i++) {
        state.enemies[i].Render(program);
    }
    
    if (state.player->dead) {
        GLuint fontTextureID = Util::LoadTexture("pixel_font.png");
        // Util::DrawText(program, fontTextureID, "You Have Died!", 0.35f, 0, glm::vec3(3.2f, -0.75f, 0));
        Util::DrawText(program, fontTextureID, "You Died!", 0.35f, 0, glm::vec3(state.player->position.x - 1.5f, state.player->position.y, 0));
    }

    state.player->Render(program);
}
