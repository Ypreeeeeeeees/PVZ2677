#include "system/Map.h"
#include "utils/Constants.h"
#include <graphics.h>

Map::Map()
    : rows(0), cols(0), cellSize(0),
      offsetX(0), offsetY(0), houseBoundaryX(0) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 9; c++) {
            grid[r][c] = nullptr;
        }
    }
}

void Map::Init(int rows, int cols, int cellSize, int offsetX, int offsetY, int houseX) {
    this->rows = rows;
    this->cols = cols;
    this->cellSize = cellSize;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->houseBoundaryX = houseX;
}

// ---- 格子占用管理 ----

bool Map::CanPlant(int row, int col) const {
    if (!IsValidCell(row, col)) return false;
    return grid[row][col] == nullptr;
}

void Map::PlantAt(int row, int col, Plant* plant) {
    if (!IsValidCell(row, col)) return;
    grid[row][col] = plant;
}

void Map::RemovePlant(int row, int col) {
    if (!IsValidCell(row, col)) return;
    grid[row][col] = nullptr;
}

Plant* Map::GetPlant(int row, int col) const {
    if (!IsValidCell(row, col)) return nullptr;
    return grid[row][col];
}

// ---- 坐标转换 ----

CellPos Map::ScreenToCell(int screenX, int screenY) const {
    int col = (screenX - offsetX) / cellSize;
    int row = (screenY - offsetY) / cellSize;
    return { row, col };
}

Point Map::CellToScreen(int row, int col) const {
    int x = offsetX + col * cellSize + cellSize / 2;
    int y = offsetY + row * cellSize + cellSize / 2;
    return { x, y };
}

bool Map::IsValidCell(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

// ---- 房子边界 ----

bool Map::HasZombieReachedHouse(float zombieX) const {
    return zombieX <= static_cast<float>(houseBoundaryX);
}

// ---- 渲染 ----

void Map::Render() {
    int mapRight  = offsetX + cols * cellSize;
    int mapBottom = offsetY + rows * cellSize;

    // 草坪底色
    setfillcolor(RGB(100, 160, 80));
    solidrectangle(offsetX, offsetY, mapRight, mapBottom);

    // 格子线
    setlinecolor(RGB(80, 140, 60));
    setlinestyle(PS_SOLID, 1);

    for (int r = 0; r <= rows; r++) {
        int y = offsetY + r * cellSize;
        line(offsetX, y, mapRight, y);
    }
    for (int c = 0; c <= cols; c++) {
        int x = offsetX + c * cellSize;
        line(x, offsetY, x, mapBottom);
    }

    // 房子区域（深灰色矩形占位）
    setfillcolor(RGB(80, 60, 40));
    solidrectangle(0, offsetY, offsetX, mapBottom);

    // 房子边界线（红色虚线，仅调试时可见，后续替换为贴图后移除）
    setlinecolor(RGB(180, 60, 60));
    setlinestyle(PS_DASH, 1);
    line(houseBoundaryX, offsetY, houseBoundaryX, mapBottom);
    setlinestyle(PS_SOLID, 1);

    // 渲染格子上的植物
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c]) {
                Point pt = CellToScreen(r, c);
                // 植物渲染由其自身 Render 完成，此处暂不实现
            }
        }
    }
}
