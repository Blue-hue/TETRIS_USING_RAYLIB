#pragma once
#include<vector>
#include<map>
#include "position.h"
#include "colors.h"

class Block{
public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int row, int col);
    std::vector<Position> GetCellPositions();
    int id;
    std::map<int, std::vector<Position>> cells;
    void Rotate();
    void undoRotate();

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int colOffset;
};