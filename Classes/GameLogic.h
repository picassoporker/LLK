#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_
#include "cocos2d.h"
#include "Item.h"
class GameLogic
{
public:
	GameLogic(void);
	~GameLogic(void);
public:
	static bool isConnet(Item* first ,Item* second,int maxRow,int maxCol ,cocos2d::Vector<Item*>itemList);
public:
	static bool line (Item* first ,Item* second,int maxRow,int maxCol ,cocos2d::Vector<Item*>itemList);
	static bool oneCorner (Item* first ,Item* second,int maxRow,int maxCol ,cocos2d::Vector<Item*>itemList);
	static bool twoCorner (Item* first ,Item* second,int maxRow,int maxCol ,cocos2d::Vector<Item*>itemList);

public:
	static std::vector<cocos2d::Point>posList;
};

#endif // !_GAME_LOGIC_H_
