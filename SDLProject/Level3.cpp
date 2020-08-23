#include "Level3.h"

#define LEVEL3_WIDTH 14
#define LEVEL3_HEIGHT 12

#define LEVEL3_ENEMYCOUNT 5

unsigned int LEVEL3_data[] = {
    145, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 147,
    
    161, 162, 160, 160, 161, 162, 162, 162, 162, 162, 162, 162, 162, 160,
    177, 176, 177, 178, 179, 176, 177, 176, 177, 176, 177, 176, 177, 178,
    176, 177, 176, 194, 195, 177, 176, 177, 176, 177, 176, 177, 176, 194,
    177, 176, 176, 178, 179, 176, 177, 176, 177, 176, 177, 176, 177, 178,
    177, 176, 176, 194, 195, 176, 177, 176, 177, 176, 177, 176, 177, 194,
    177, 176, 176, 176, 176, 176, 177, 176, 177, 176, 177, 176, 177, 178,
    177, 176, 176, 176, 176, 176, 177, 176, 177, 176, 177, 176, 177, 194,
    
    139, 140, 139, 140, 139, 140, 139, 140, 139, 140, 139, 140, 139, 140,
    155, 156, 155, 156, 155, 156, 155, 156, 155, 156, 155, 156, 155, 156,
    155, 156, 155, 156, 155, 156, 155, 156, 155, 156, 155, 156, 155, 156
};

void Level3::Initialize() {
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("dungeon-v2-tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, LEVEL3_data, mapTextureID, 1.0f, 16, 16);
    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1, -2, 0);
    state.player->movement = glm::vec3(0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("player.png");
    
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
    
    state.player->height = 1.0f;
    state.player->width = 1.0f;
    

    state.enemies = new Entity[LEVEL3_ENEMYCOUNT];
    GLuint enemyTextureID = Util::LoadTexture("orc.png");
    
    for (int i = 0; i < LEVEL3_ENEMYCOUNT; i++) {
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
    state.enemies[0].position = glm::vec3(10, -3, 0);
    state.enemies[0].speed = 0.65;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = PATROL_X;
    state.enemies[0].height = 0.0;
    state.enemies[0].width = 0.0;

    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(10, -5, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = PATROL_X;
    state.enemies[1].height = 0.0;
    state.enemies[1].width = 0.0;

    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(10, -4, 0);
    state.enemies[2].speed = 0.85;
    state.enemies[2].aiType = WAITANDGO;
    state.enemies[2].aiState = PATROL_X;
    state.enemies[2].height = 0.0;
    state.enemies[2].width = 0.0;
    
    state.enemies[3].entityType = ENEMY;
    state.enemies[3].textureID = enemyTextureID;
    state.enemies[3].position = glm::vec3(10, -2, 0);
    state.enemies[3].speed = 0.85;
    state.enemies[3].aiType = WAITANDGO;
    state.enemies[3].aiState = PATROL_X;
    state.enemies[3].height = 0.0;
    state.enemies[3].width = 0.0;
    
    state.enemies[4].entityType = ENEMY;
    state.enemies[4].textureID = enemyTextureID;
    state.enemies[4].position = glm::vec3(2, -7, 0);
    state.enemies[4].speed = 0.75;
    state.enemies[4].aiType = WAITANDGO;
    state.enemies[4].aiState = PATROL_Y;
    state.enemies[4].height = 0.0;
    state.enemies[4].width = 0.0;
    state.enemies[4].animIndices = state.enemies[4].animUp;

}

void Level3::Update(float deltaTime) {
    for (int i = 0; i < LEVEL3_ENEMYCOUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMYCOUNT, state.map);
    }
    
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMYCOUNT, state.map);
}

void Level3::Render(ShaderProgram *program) {
    state.map->Render(program);
    
    for (int i = 0; i  < LEVEL3_ENEMYCOUNT; i++) {
        state.enemies[i].Render(program);
    }
    
    bool enemiesAlive = false;
    for (int i = 0; i < LEVEL3_ENEMYCOUNT; i++) {
        if (!state.enemies[i].dead) enemiesAlive = true;
    }
    
    if (state.player->dead) {
        GLuint fontTextureID = Util::LoadTexture("pixel_font.png");
        Util::DrawText(program, fontTextureID, "You Died!", 0.35f, 0, glm::vec3(state.player->position.x - 1.5f, state.player->position.y, 0));
    }
    else if (!state.player->dead && !enemiesAlive) {
        GLuint fontTextureID = Util::LoadTexture("pixel_font.png");
        Util::DrawText(program, fontTextureID, "You Win!", 0.35f, 0, glm::vec3(state.player->position.x - 1.5f, state.player->position.y + 0.75f, 0));
        state.player->isActive = false;
    }

    state.player->Render(program);
}
