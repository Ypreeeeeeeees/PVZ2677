#ifndef PVZ_MAP_H
#define PVZ_MAP_H

class Plant;

struct CellPos {
    int row;
    int col;
};

struct Point {
    int x;
    int y;
};

class Map {
public:
    Map();

    void Init(int rows, int cols, int cellSize, int offsetX, int offsetY, int houseX);

    // ---- 格子占用管理 ----
    bool   CanPlant(int row, int col) const;
    void   PlantAt(int row, int col, Plant* plant);
    void   RemovePlant(int row, int col);
    Plant* GetPlant(int row, int col) const;

    // ---- 坐标转换 ----
    CellPos ScreenToCell(int screenX, int screenY) const;
    Point   CellToScreen(int row, int col) const;
    bool    IsValidCell(int row, int col) const;

    // ---- 房子边界 ----
    int  GetHouseBoundaryX() const { return houseBoundaryX; }
    bool HasZombieReachedHouse(float zombieX) const;

    // ---- 地图区域访问 ----
    int GetOffsetX() const { return offsetX; }
    int GetOffsetY() const { return offsetY; }
    int GetCellSize() const { return cellSize; }
    int GetRows() const { return rows; }
    int GetCols() const { return cols; }

    // ---- 渲染 ----
    void Render();

private:
    int rows;
    int cols;
    int cellSize;
    int offsetX;
    int offsetY;
    int houseBoundaryX;
    Plant* grid[5][9];          // 固定 5×9，architecture 定义
};

#endif // PVZ_MAP_H
