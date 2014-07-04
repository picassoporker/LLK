#include "MapLayer.h"
#include "GameLogic.h"
USING_NS_CC;

MapLayer::MapLayer(void) :   mapRowMax(6),
											mapColMax(10),
											itemList(),
											mapSize(),
											winSize(),
											firstItem(nullptr),
											secondItem(nullptr),
											ah(255)
{
}


MapLayer::~MapLayer(void)
{
}

Scene* MapLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = MapLayer::create();
	sc->addChild(ly);
	return sc;
}

bool MapLayer::init()
{
	Layer::init();
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mhxy.plist");
	//Sprite* bg = Sprite::createWithSpriteFrameName("bg.png");
	//this->addChild(bg);
	//bg->setAnchorPoint(Point::ZERO);
	winSize = Director::getInstance() ->getVisibleSize();
	mapSize = Size(mapColMax * ITEM_GAP,mapRowMax * ITEM_GAP);
	createMap();
	addEvent();
	return true;
}

void MapLayer::createMap()
{
	Item* mItem = NULL;
	int type = 0 ;
	for (int i = 0; i < mapRowMax; i++)
	{
		for (int	j = 0; j< mapColMax; j++)
		{
			if (i == 0 || j == 0 || i ==mapRowMax - 1 || j ==mapColMax - 1)
			{
				mItem	=	Item ::create(); 
				mItem->setIsPass(true);
				mItem->setRowAndCol(i,j);
				mItem->setPosition( j * ITEM_GAP + (winSize.width - mapSize.width) / 2,
												i * ITEM_GAP + (winSize.height - mapSize.height) / 2);
			}else 
			{
				mItem	=	Item ::create(); 
				mItem->setIsPass(false);
				type = CCRANDOM_0_1() * 15 + 1;
				mItem->initItem(type,i,j);
				this->addChild(mItem);
				mItem->setPosition( j * ITEM_GAP + (winSize.width - mapSize.width) / 2,
												i * ITEM_GAP + (winSize.height - mapSize.height) / 2);
			}
			itemList.pushBack(mItem);
		}
	}
}

bool MapLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{

	
	Point touchPos  = touch->getLocation();
	Point zeroPos	 = Point(winSize.width /2  - mapSize.width /2 ,winSize.height / 2 - mapSize.height / 2);
	Point dPos		 = touchPos - zeroPos ;

	if (dPos.x < 0 || dPos.y < 0 || dPos.x >mapSize.width || dPos.y > mapSize.height)
	{
		return true;
	}
	int r					 = dPos.y / ITEM_GAP;
	int c					 = dPos.x / ITEM_GAP;

	if (!firstItem)
	{
		firstItem = getItemByRowAndCol(r,c);
		firstItem->startScaleAction();
	}else if (!secondItem)
	{
		secondItem = getItemByRowAndCol(r,c);
		firstItem->stopScaleAction();
		if (firstItem->getType() == secondItem->getType() && 
			GameLogic::isConnet(firstItem,secondItem,mapRowMax,mapColMax,itemList))
		{
			firstItem->disappear();
			secondItem->disappear();
			this->removeChild(firstItem);
			this->removeChild(secondItem);
			firstItem->setIsPass(true);
			secondItem->setIsPass(true);
			ah = 255;
		}
		firstItem = NULL;
		secondItem =NULL;
	}
	return true;
}

Item*  MapLayer::getItemByRowAndCol(int r ,int c)
{
	int index = r * mapColMax  +  c;
	return itemList.at(index);
}

void MapLayer::addEvent()
{
	EventListenerTouchOneByOne* evtTouch = EventListenerTouchOneByOne::create();
	evtTouch->onTouchBegan						=	CC_CALLBACK_2(MapLayer::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evtTouch,this);
}

void MapLayer::draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	Layer::draw(renderer,transform,transformUpdated);
	CHECK_GL_ERROR_DEBUG();
	glLineWidth(3);
	DrawPrimitives::setDrawColor4B(255,255,255,ah);
	Point pos ;
	Point next;
	if (ah > 0)
	{
		ah -= 5;
	}
	for (int i = 0; i < int(GameLogic::posList.size() - 1); i++)
	{
		pos = GameLogic::posList[i] +Point(40,40) ;
		next = GameLogic::posList[i + 1] +Point(40,40);
		DrawPrimitives::drawLine(pos,next);

	}
}