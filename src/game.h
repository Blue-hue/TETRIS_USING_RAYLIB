#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game{
public:
    Game();
    ~Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw();

    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    Grid grid;
    bool gameover;
    void Reset();
    int score;
    void updateScore(int linesCleared, int moveDownPoints);
    Music music;

private:
    std::vector<Block> blocks;
    Block currBlock;
    Block nextBlock;
    bool isBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    Sound rotatesound;
    Sound clearsound;
    
};

