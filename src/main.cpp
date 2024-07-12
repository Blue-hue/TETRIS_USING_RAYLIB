#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval){
    double currTime = GetTime();
    if (currTime-lastUpdateTime>=interval){
        lastUpdateTime = currTime;
        return true;
    }
    return false;
}

int main()
{

    InitWindow(500,630, "TETRIS-GAME");
    SetTargetFPS(60); //frame-rate set

    Font font = LoadFontEx("assets/fonts/3Dumb.ttf", 64, 0, 0);

    Game game = Game();

    while(WindowShouldClose()==false){
        UpdateMusicStream(game.music);
        game.HandleInput();
        if(EventTriggered(0.2)){
             game.MoveBlockDown();
             game.updateScore(0, 1);
        }
        BeginDrawing();
        ClearBackground(darkblue); 
        DrawTextEx(font, "Score", {360, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {365, 175}, 38, 2, WHITE);
        if(game.gameover){
            DrawTextEx(font, "Game over", {320, 450}, 30, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightblue);
        char scoretext[10];
        sprintf(scoretext, "%d", game.score);
        Vector2 textsize = MeasureTextEx(font, scoretext, 38, 2);

        DrawTextEx(font, scoretext, {320 + (170-textsize.x)/2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightblue);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}