#include "PvZ/Lawn/Board/CutScene.h"
#include "PvZ/Enums.h"
#include "PvZ/Lawn/Board/Board.h"
#include "PvZ/Lawn/LawnApp.h"

void CutScene_ShowShovel(CutScene *cutScene) {
    LawnApp *lawnApp = cutScene->mApp;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
        // 不绘制锤子铲子黄油按钮
        Board *board = cutScene->mBoard;
        board->mShowShovel = false;
        board->mShowButter = false;
        board->mShowHammer = false;
        return;
    }
    return old_CutScene_ShowShovel(cutScene);
}


void CutScene_Update(CutScene *cutScene) {
    return old_CutScene_Update(cutScene);
}
