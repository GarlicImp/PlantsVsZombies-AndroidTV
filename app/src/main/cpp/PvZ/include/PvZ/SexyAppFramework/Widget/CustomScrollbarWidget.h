//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_CUSTOMSCROLLBARWIDGET_H
#define PLANTSVSZOMBIES_ANDROIDTV_CUSTOMSCROLLBARWIDGET_H

#include "ScrollbarWidget.h"

namespace Sexy {

class CustomScrollbarWidget : public ScrollbarWidget {
    // 没有新增任何成员，6，这个类不知道什么意义
}; // 大小90个整数

}

void CustomScrollbarWidget_RemoveScrollButtons(Sexy::CustomScrollbarWidget *scrollbarWidget);

#endif // PLANTSVSZOMBIES_ANDROIDTV_CUSTOMSCROLLBARWIDGET_H
