#include "game.h"
#include<random>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameover = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("assets/sounds/music.mp3");
    PlayMusicStream(music);
    rotatesound = LoadSound("assets/sounds/rotate.mp3");
    clearsound = LoadSound("assets/sounds/clear.mp3");
}

Game::~Game(){
    UnloadSound(rotatesound);
    UnloadSound(clearsound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock(){
    if(blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(){
    grid.Draw();
    currBlock.Draw(11, 11);
    switch(nextBlock.id){
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
            break;
    }

}

void Game::HandleInput(){
    int keyPressed = GetKeyPressed();
    if(gameover && keyPressed!=0){
        gameover = false;
        Reset();
    }
    switch(keyPressed){
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_UP:
            RotateBlock();
            break;
        

    }
}

void Game::MoveBlockLeft(){
    if(!gameover){
        currBlock.Move(0,-1);
        if(isBlockOutside() || BlockFits()==false) currBlock.Move(0,1);
    }
    
}


void Game::MoveBlockRight(){
    if(!gameover){
        currBlock.Move(0,1);
        if(isBlockOutside() || BlockFits()==false) currBlock.Move(0,-1);
    }
}

void Game::MoveBlockDown(){
    if(!gameover){
        currBlock.Move(1,0);
        if(isBlockOutside() || BlockFits()==false){
            currBlock.Move(-1,0);
            LockBlock();
        }
    }
}

void Game::Reset(){
    grid.Initialize();
    blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for(Position item:tiles){
        if(grid.isCellOutside(item.row, item.col)) return true;
    }
    return false;
}

void Game::RotateBlock(){
    if(!gameover){
        currBlock.Rotate();
        if(isBlockOutside() || BlockFits()==false) currBlock.undoRotate();
        else{
            PlaySound(rotatesound);
        }
    }
}

void Game::LockBlock(){
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for(Position item:tiles){
        grid.grid[item.row][item.col] = currBlock.id;
    }
    currBlock = nextBlock;
    if(BlockFits()==false){
        gameover = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.clearFullRows();
    if(rowsCleared>0){
        PlaySound(clearsound);
        updateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for(Position item:tiles){
        if(grid.isCellEmpty(item.row, item.col)==false) return false;
    }
    return true;
}

void Game::updateScore(int linesCleared, int moveDownPoints){
    switch(linesCleared){
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score+=700;
            break;
        default:
            break;
    }
    score += moveDownPoints;
    if(gameover) score-=1;
}
