#ifndef _ITEM_H_
#define _ITEM_H_
#include "cocos2d.h"
class Item : public cocos2d :: Sprite
{
public:
	Item(void);
	~Item(void);
	virtual bool init();
	CREATE_FUNC(Item);

public:
	void setRowAndCol(int r ,int c);
	int getRow()const;
	int getCol()const;
	void setIsPass(bool bl);
	bool getIsPass()const;
	void initItem(int type ,int r,int c);
	int  getType()const ;
	void startScaleAction();
	void stopScaleAction();
	void disappear();
private:
	int row;
	int col;
	bool isPass;
	int type ;
};

#endif // !_ITEM_H_
