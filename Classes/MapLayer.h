#ifndef _MAP_LAYER_H_
#define _MAP_LAYER_H_
#include "cocos2d.h"
#include "Item.h"
class MapLayer : public cocos2d::Layer
{
public:
	MapLayer(void);
	~MapLayer(void);
	virtual bool init();
	virtual void draw(cocos2d::Renderer * renderer,const kmMat4 &transform,bool transformUpdated);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	CREATE_FUNC(MapLayer);

public:
	static cocos2d::Scene* createScene();

private:
	 void createMap();
	 Item*  getItemByRowAndCol(int r ,int c);
	 void addEvent();
private:
	static const int ITEM_GAP = 80 ;
	int mapRowMax;
	int mapColMax;
	cocos2d::Size winSize ;
	cocos2d::Size mapSize;
	cocos2d::Vector<Item*> itemList;
	Item*  firstItem ;
	Item * secondItem;
	unsigned int ah ;
};
#endif // _MAP_LAYER_H_

