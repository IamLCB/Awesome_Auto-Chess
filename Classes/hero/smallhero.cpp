#include "smallhero.h"

smallHero* smallHero::initSmall()
{
    smallHero* smallmy = smallHero::create();
    smallmy->picturename = "./hero/smallhero.png";
    smallmy->picturenum = 1;
    smallmy->heroAnimation(smallmy->picturename, smallmy->picturenum, smallmy, speed, -1);
    return smallmy;
}

void smallHero::moveByMouse_R(Hero* myHero) {
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = [this, myHero](Event* event) { // 使用捕获列表捕获 this 和 myHero
        auto mouseEvent = static_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
        {
            auto location = mouseEvent->getLocationInView();
            // 在这里添加一个停止所有动作的调用，以防止动作冲突
            myHero->runAction(MoveTo::create(1.0f, location));
        }
    };

    // 确保事件分发器被正确添加
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, myHero);
}