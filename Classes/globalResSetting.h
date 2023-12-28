#ifndef __GLOBAL_RES_SETTING_H__
#define __GLOBAL_RES_SETTING_H__

#define BG_SCALE 1.3
#define BG_PNG "./mainMenu/mainMenuBackground.png"
#define BG_BTNS "./mainMenu/menuBTNS.png"

#define CENTER_WIN Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)
#define CENTER_WIN_X visibleSize.width / 2 + origin.x
#define CENTER_WIN_Y visibleSize.height / 2 + origin.y

#define LEFT_WIN_X origin.x
#define RIGHT_WIN_X origin.x + visibleSize.width
#define BOTTOM_WIN_Y origin.y 
#define TOP_WIN_Y origin.y + visibleSize.height

#define LEFT_BOTTOM_WIN Vec2(origin.x, origin.y)
#define LEFT_TOP_WIN Vec2(origin.x, origin.y + visibleSize.height)
#define RIGHT_BOTTOM_WIN Vec2(origin.x + visibleSize.width, origin.y)
#define RIGHT_TOP_WIN Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height)

#define TFNS 1


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

#endif // __GLOBAL_RES_SETTING_H__
