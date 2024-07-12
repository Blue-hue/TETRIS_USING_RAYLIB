#pragma once
#include <vector>
#include <raylib.h>

class Grid{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool isCellOutside(int row, int col);
    int grid[20][10];
    bool isCellEmpty(int row, int col);
    int clearFullRows();


private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    bool isRowEmpty(int row);
    void clearRow(int row);
    void moveRowDown(int row, int num);

};