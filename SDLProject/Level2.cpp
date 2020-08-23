#include "Level2.h"

#define LEVEL2_WIDTH 31
#define LEVEL2_HEIGHT 9

#define LEVEL2_ENEMYCOUNT 3

unsigned int LEVEL2_data[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2,
    17, 18, 18, 18, 17, 18, 18, 18, 18, 18, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 17, 18, 18, 18, 18, 17, 18, 18, 18, 18,
    160, 160, 160, 161, 163, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 160,
    178, 179, 176, 177, 176, 176, 176, 177, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 178,
    194, 195, 192, 193, 192, 192, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 194,
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void Level2::Initialize() {
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("dungeon-v2-tileset.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, LEVEL2_data, mapTextureID, 1.0f, 16, 16);
    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(4, -4, 0);
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
    
    // state.player->dashPower = 10.0f;
    
    state.enemies = new Entity[LEVEL2_ENEMYCOUNT];
    GLuint enemyTextureID = Util::LoadTexture("orc.png");
    
    for (int i = 0; i < LEVEL2_ENEMYCOUNT; i++) {
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
    state.enemies[0].position = glm::vec3(27, -3, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = PATROL_X;
    state.enemies[0].height = 0.0;
    state.enemies[0].width = 0.0;

    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(27, -5, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = PATROL_X;
    state.enemies[1].height = 0.0;
    state.enemies[1].width = 0.0;
    
    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(27, -4, 0);
    state.enemies[2].speed = .5;
    state.enemies[2].aiType = WAITANDGO;
    state.enemies[2].aiState = PATROL_X;
    state.enemies[2].height = 0.0;
    state.enemies[2].width = 0.0;
}

void Level2::Update(float deltaTime) {
    for (int i = 0; i < LEVEL2_ENEMYCOUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMYCOUNT, state.map);
    }
    
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMYCOUNT, state.map);
    
    // If all enemies are dead and player is alive, proceed to next scene
    bool enemiesAlive = false;
    for (int i = 0; i < LEVEL2_ENEMYCOUNT; i++) {
        if (!state.enemies[i].dead) enemiesAlive = true;
    }
    
    if (!enemiesAlive && !state.player->dead) state.nextScene = 3;
}

void Level2::Render(ShaderProgram *program) {
    state.map->Render(program);
    
    for (int i = 0; i  < LEVEL2_ENEMYCOUNT; i++) {
        state.enemies[i].Render(program);
    }
    
    if (state.player->dead) {
        GLuint fontTextureID = Util::LoadTexture("pixel_font.png");
        Util::DrawText(program, fontTextureID, "You Died!", 0.35f, 0, glm::vec3(state.player->position.x - 1.5f, state.player->position.y, 0));
    }
    
    state.player->Render(program);
}
