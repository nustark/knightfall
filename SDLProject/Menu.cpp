    //#include "Menu.h"

    //void Menu::Initialize() {
    //    state.nextScene = -1;
    //}
    //
    //void Menu::Update(float deltaTime) {
    //    if (state.nextScene == 0) {
    //        state.nextScene = 0;
    //    }
    //}
    //
    //void Menu::Render(ShaderProgram *program) {
    //    state.map->Render(program);
    //    state.player->Render(program);
    //}

#include "Menu.h"

#define MENU_WIDTH 14
#define MENU_HEIGHT 8

#define MENU_ENEMYCOUNT 1

    //unsigned int menu_data[] = {
    //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //    0, 0, 0, 0, 48, 49, 49, 50, 0, 0, 0, 0, 0, 0,
    //    48, 49, 49, 49, 49, 50, 0, 0, 0, 0, 0, 0, 0, 0
    //};

unsigned int menu_data[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void Menu::Initialize() {
    state.nextScene = -2;
    
    GLuint mapTextureID = Util::LoadTexture("dungeon-v1-tileset.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 1.0f, 14, 8);
    
    // Initialize Game Objects
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(-10, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("player.png");
    
    state.player->animRight = new int[4] {3, 7, 11, 15};
    state.player->animLeft = new int[4] {1, 5, 9, 13};
    state.player->animUp = new int[4] {2, 6, 10, 14};
    state.player->animDown = new int[4] {0, 4, 8, 12};
    
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;
    
    state.player->height = 0.8f;
    state.player->width = 0.8f;
    
    state.player->jumpPower = 6.0f;
    
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
    
    state.enemies = new Entity[MENU_ENEMYCOUNT];
    GLuint enemyTextureID = Util::LoadTexture("orc.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(4, -2.25, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].isActive = false;
}

void Menu::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, MENU_ENEMYCOUNT, state.map);
}

void Menu::Render(ShaderProgram *program) {
    state.map->Render(program);
    
    GLuint fontTextureID = Util::LoadTexture("pixel_font.png");
    Util::DrawText(program, fontTextureID, "Dungeon Dash", 0.65f, 0, glm::vec3(1.25f, -1.75f, 0));
    
    Util::DrawText(program, fontTextureID, "Defeat all enemies to proceed.", 0.20f, 0, glm::vec3(2.0f, -2.75f, 0));
    Util::DrawText(program, fontTextureID, "Controls:", 0.18f, 0, glm::vec3(3.0f, -3.75f, 0));
    Util::DrawText(program, fontTextureID, "Arrow Keys to Move", 0.18f, 0, glm::vec3(3.0f, -4.25f, 0));
    Util::DrawText(program, fontTextureID, "Hold Space to Swing Sword", 0.18f, 0, glm::vec3(3.0f, -4.5f, 0));
    Util::DrawText(program, fontTextureID, "Press Enter to Start", 0.18f, 0, glm::vec3(3.0f, -5.75f, 0));
    
    state.player->Render(program);
}
