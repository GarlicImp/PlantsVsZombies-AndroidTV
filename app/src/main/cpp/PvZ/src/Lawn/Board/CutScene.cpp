#include "PvZ/Lawn/Board/CutScene.h"
#include "PvZ/Lawn/Board/Board.h"
#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/Lawn/LawnApp.h"

void CutScene::ShowShovel() {
    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
        // 不绘制锤子铲子黄油按钮
        mBoard->mShowShovel = false;
        mBoard->mShowButter = false;
        mBoard->mShowHammer = false;
        return;
    }

    return old_CutScene_ShowShovel(this);
}


void CutScene::Update() {
    return old_CutScene_Update(this);
}
