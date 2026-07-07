#include "core/Game.h"
#include <graphics.h>
#include "utils/Constants.h"

int main() {
    Game& game = Game::GetInstance();

    if (!game.Init(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT,
                   L"植物大战僵尸 Lite")) {
        return -1;
    }

    game.Run();

    closegraph();
    return 0;
}
