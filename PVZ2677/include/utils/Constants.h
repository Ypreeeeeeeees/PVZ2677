#ifndef PVZ_CONSTANTS_H
#define PVZ_CONSTANTS_H

namespace GameConstants {

    // ---- 窗口 ----
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr int TARGET_FPS = 60;

    // ---- 地图 ----
    constexpr int MAP_ROWS = 5;
    constexpr int MAP_COLS = 9;
    constexpr int CELL_SIZE = 110;               // 每格边长（正方形）
    constexpr int MAP_OFFSET_X = 145;            // 草坪左边界 X
    constexpr int MAP_OFFSET_Y = 100;            // 草坪上边界 Y（卡槽下方）
    constexpr int MAP_GRID_WIDTH = MAP_COLS * CELL_SIZE;   // 990
    constexpr int MAP_GRID_HEIGHT = MAP_ROWS * CELL_SIZE;  // 550
    constexpr int HOUSE_BOUNDARY_X = 120;        // 房子左边界线

    // ---- 阳光 ----
    constexpr int INITIAL_SUN = 150;
    constexpr int SUN_VALUE = 25;
    constexpr float NATURAL_SUN_INTERVAL = 10.0f;
    constexpr float SUN_LIFETIME = 8.0f;

    // ---- 向日葵 ----
    constexpr int SUNFLOWER_PRICE = 50;
    constexpr int SUNFLOWER_HEALTH = 300;
    constexpr float SUNFLOWER_COOLDOWN = 7.5f;
    constexpr float SUNFLOWER_PRODUCE_INTERVAL = 24.0f;

    // ---- 豌豆射手 ----
    constexpr int PEASHOOTER_PRICE = 100;
    constexpr int PEASHOOTER_HEALTH = 300;
    constexpr float PEASHOOTER_COOLDOWN = 7.5f;
    constexpr float PEASHOOTER_ATTACK_INTERVAL = 1.5f;
    constexpr int PEA_DAMAGE = 20;
    constexpr float PEA_SPEED = 150.0f;

    // ---- 普通僵尸 ----
    constexpr int NORMAL_ZOMBIE_HEALTH = 200;
    constexpr float NORMAL_ZOMBIE_SPEED = 20.0f;
    constexpr int NORMAL_ZOMBIE_ATTACK = 10;

    // ---- 铁桶僵尸 ----
    constexpr int BUCKET_ZOMBIE_HEALTH = 600;
    constexpr float BUCKET_ZOMBIE_SPEED = 18.0f;

    // ---- 启动界面 ----
    constexpr float SPLASH_DURATION = 2.0f;

    // ---- UI 颜色 ----
    constexpr int COLOR_BG = 0x2D5A27;           // 深绿色背景
    constexpr int COLOR_BUTTON_NORMAL = 0x4A8C3F; // 按钮普通
    constexpr int COLOR_BUTTON_HOVER = 0x6DBF5B;  // 按钮悬停
    constexpr int COLOR_BUTTON_TEXT = 0xFFFFFF;   // 按钮文字白色
    constexpr int COLOR_TITLE = 0xFFD700;         // 标题金色
    constexpr int COLOR_OVERLAY = 0x88000000;     // 半透明遮罩

    // ---- 按钮尺寸 ----
    constexpr int BUTTON_WIDTH = 200;
    constexpr int BUTTON_HEIGHT = 50;
    constexpr int BUTTON_RADIUS = 8;              // 圆角半径

}

#endif // PVZ_CONSTANTS_H
