#include "easysolomode.h"
#include "Joueur.h"

Easysolomode::Easysolomode() : maze(35, 35), player(1, 1, 4.0f), gameWon(false) {
    backgroundTexture = LoadTexture("images/hard.png"); 
    settingsButtonTexture = LoadTexture("buttons/butto/Back MAZE.png");
 
    float buttonWidth = (float)settingsButtonTexture.width;
    float buttonHeight = (float)settingsButtonTexture.height;
    settingsButton = { GetScreenWidth() - buttonWidth - 20.0f, 20.0f, buttonWidth, buttonHeight }; 

    chronoPosition = { 20.0f, 20.0f }; 
    mazeArea = { GetScreenWidth() * 0.2f, GetScreenHeight() * 0.2f, GetScreenWidth() * 0.6f, GetScreenHeight() * 0.6f }; 

    startTime = GetTime(); 
}

Easysolomode::~Easysolomode() {
    UnloadTexture(backgroundTexture);
    UnloadTexture(settingsButtonTexture);
}

GameScreen Easysolomode::Update() {
    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, settingsButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return DIFFICULTY;
    }

    player.Update(maze);

    if (player.x >= maze.finishX - 1 && player.x <= maze.finishX + 1 &&
        player.y >= maze.finishY - 1 && player.y <= maze.finishY + 1 && !gameWon) {
        gameWon = true;
        finalTime = GetTime() - startTime; 
    }

    return EASYSOLOMODE;
}

void Easysolomode::Draw() {

    DrawTexture(backgroundTexture, 0, 0, WHITE);

    DrawTexture(settingsButtonTexture, (int)settingsButton.x, (int)settingsButton.y, WHITE);

    DrawTexture(chronoIconTexture, (int)chronoPosition.x, (int)chronoPosition.y, WHITE);

    float mazeCenterX = GetScreenWidth() / 2 - mazeArea.width / 2 + 250;  
    float mazeCenterY = GetScreenHeight() / 2 - mazeArea.height / 2 + 20; 

    double elapsedTime = 0;
    if (!gameWon) {
        elapsedTime = GetTime() - startTime; 
        DrawText(TextFormat("Time: %.2f s", elapsedTime), (int)(chronoPosition.x + chronoIconTexture.width + 37), (int)chronoPosition.y + 25, 25, BLACK);
    }

    for (int i = 0; i < maze.hauteur; ++i) {
        for (int j = 0; j < maze.largeur; ++j) {
            Color color;
            if (maze.grille[i][j] == 1) {
                color = BROWN;
            } else if (maze.grille[i][j] == 2) {
                color = GREEN;
            } else {
                color = LIGHTGRAY;
            }
            DrawRectangle(j * cellSize + mazeCenterX, i * cellSize + mazeCenterY, cellSize, cellSize, color);
        }
    }
    
    player.Draw(mazeCenterX, mazeCenterY);

    if (gameWon) {
        DrawText("Congratulations! You finished the easy maze!", GetScreenWidth() / 2 - 320, GetScreenHeight() / 2 + 20,30, GREEN);
        DrawText(TextFormat("Your time: %.2f s", finalTime), GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 150, 35, BLACK);
    }
}
