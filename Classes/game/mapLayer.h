#ifndef _MAP_LAYER_H_
#define _MAP_LAYER_H_

#define NO_CHESS 0
#define CHESS_IN_A_ROW 7
#define CHESS_IN_A_COL 6
#define MAX_CHESS CHESS_IN_A_ROW*CHESS_IN_A_COL
#define EFFRADIUS 10 // ´ýÐÞÕý °ë¾¶

#include"cocos2d.h"
#include <vector>
USING_NS_CC;

using std::vector;

extern vector<vector<Point>>chessMap;
extern vector<vector<bool>>haveChess;

class mapLayer : public Layer 
{
public:
	static mapLayer* createMapLayer();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(mapLayer);

	//Point chessMap[CHESS_IN_A_ROW][CHESS_IN_A_COL];
	//bool haveChess[CHESS_IN_A_ROW][CHESS_IN_A_COL];


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