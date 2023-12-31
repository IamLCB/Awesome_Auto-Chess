#ifndef _MAP_LAYER_H_
#define _MAP_LAYER_H_

#define NO_CHESS 0
#define EFF_RADIUS 30 // ´ýÐÞÕý °ë¾¶

#include"cocos2d.h"
#include"globalResSetting.h"
#include <vector>

USING_NS_CC;

extern Point chessMap[CHESS_IN_A_COL + 2][CHESS_IN_A_ROW];
extern bool haveChess[CHESS_IN_A_COL + 2][CHESS_IN_A_ROW];

class mapLayer : public Layer
{
public:
	static mapLayer* createMapLayer();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(mapLayer);

};
struct Pair
{
	int x;
	int y;

	Pair(int x1, int y1)
	{
		x = x1;
		y = y1;
	}
	Pair() { x = 0; y = 0; };
};

Pair pairReturn(Point point);

#endif // !_MAP_LAYER_H_