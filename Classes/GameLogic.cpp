#include "GameLogic.h"
#include "MapLayer.h"
USING_NS_CC;
std::vector<Point>GameLogic::posList;
GameLogic::GameLogic(void) 
{
}


GameLogic::~GameLogic(void)
{
}
bool GameLogic::line (Item* first ,Item* second,int maxRow,int maxCol ,cocos2d::Vector<Item*>itemList)
{
	
	int r1 = first->getRow();
	int c1 = first->getCol();
	int r2 = second->getRow();
	int c2 = second->getCol();
	if (first == second || r1 != r2 && c1 != c2)
	{
		return false;
	}
	
	if (c1 == c2)
	{
		int beginRow			= r1 > r2 ? r2 : r1;
		int endRow				= r1 > r2 ? r1 : r2;
		int indexNext			= 0;
		Item* nextItem			= nullptr;
		for (int i = beginRow + 1; i < endRow; i++)
		{
			indexNext		= i * maxCol + c1;
			nextItem		= itemList.at(indexNext);
			if (nextItem->getIsPass() ==false)
			{
				return false;
			}
		}
	}

	if (r1 == r2)
	{
		int beginCol  = c1 > c2 ? c2 : c1;
		int endCol		 = c1 > c2 ? c1 : c2;
		int indexNext			= 0;
		Item* nextItem			= NULL;
		for (int i = beginCol + 1; i < endCol; i++)
		{
			indexNext		= r1 * maxCol + i;
			nextItem		= itemList.at(indexNext);
			if (nextItem->getIsPass() ==false)
			{
				return false;
			}
		}
	}
	return true;
}
bool GameLogic::isConnet(Item* first ,Item* second,int maxRow,int maxCol ,cocos2d::Vector<Item*>itemList)
{
	posList.clear();
	posList.push_back(first->getPosition());
	posList.push_back(second->getPosition());
	if (line(first,second,maxRow,maxCol ,itemList) || 
		oneCorner(first,second,maxRow,maxCol ,itemList)
		|| twoCorner(first,second,maxRow,maxCol ,itemList))
	{
		for (int i = 0; i < posList.size(); i++)
		{
			log("%d __ x: %f __ y:%f ",posList.size(),
				posList[i].x,posList[i].y);
		}
		return true;
	}
		return false;
	
}
bool GameLogic::oneCorner (Item* first ,Item* second,int maxRow,int maxCol ,cocos2d::Vector<Item*>itemList)
{
	int cornerRowA	=	first->getRow();
	int cornerColA	=	second->getCol();
	int cornerIndexA = cornerRowA * maxCol +cornerColA;
	Item* cornerA	=	itemList.at(cornerIndexA);
	if (cornerA->getIsPass() && line(first,cornerA,maxRow,maxCol,itemList) && line(second,cornerA,maxRow,maxCol,itemList))
	{
		posList.insert(posList.begin() + 1,cornerA->getPosition());
		return true;
	}
	int cornerRowB	=	second->getRow();
	int cornerColB=	first->getCol();
	int cornerIndexB = cornerRowB * maxCol +cornerColB;
	Item* cornerB	=	itemList.at(cornerIndexB);
	if (cornerB->getIsPass() && line(first,cornerB,maxRow,maxCol,itemList) && line(second,cornerB,maxRow,maxCol,itemList))
	{
		posList.insert(posList.begin() + 1,cornerB->getPosition());
		return true;
	}
	return false;
}

bool GameLogic::twoCorner (Item* first ,Item* second,int maxRow,int maxCol ,cocos2d::Vector<Item*>itemList)
{
	//向下遍历
	int r1 = first->getRow();
	int c1 = first->getCol();
	Item* getItem = NULL;
	for (int i = r1 - 1; i >= 0; i--)
	{
		int index = i * maxCol + c1;
		getItem = itemList.at(index);
		if (!getItem->getIsPass() )
		{
			break;
		}else if(oneCorner(getItem,second,maxRow,maxCol,itemList))
		{
			posList.insert(posList.begin() + 1,getItem->getPosition());
			return true;
		}
	}
	//向上遍历
	for (int i = r1 + 1; i < maxRow; i++)
	{
		int index = i * maxCol + c1;
		getItem = itemList.at(index);
		if (!getItem->getIsPass() )
		{
			break;
		}else if(oneCorner(getItem,second,maxRow,maxCol,itemList))
		{
			posList.insert(posList.begin() + 1,getItem->getPosition());
			return true;
		}
	}
	//向左遍历
	for (int i = c1 - 1; i >= 0; i--)
	{
		int index = r1 * maxCol + i;
		getItem = itemList.at(index);
		if (!getItem->getIsPass() )
		{
			break;
		}else if(oneCorner(getItem,second,maxRow,maxCol,itemList))
		{
			posList.insert(posList.begin() + 1,getItem->getPosition());
			return true;
		}
	}
	//向右遍历
	for (int i = c1 + 1; i < maxCol; i++)
	{
		int index = r1 * maxCol + i;
		getItem = itemList.at(index);
		if (!getItem->getIsPass() )
		{
			break;
		}else if(oneCorner(getItem,second,maxRow,maxCol,itemList))
		{
			posList.insert(posList.begin() + 1,getItem->getPosition());
			return true;
		}
	}
	return false;
}