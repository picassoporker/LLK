#include "Item.h"
USING_NS_CC;

Item::Item(void) :  row(0),
							col(0),
							isPass(false)
{
}


Item::~Item(void)
{
}

bool Item::init()
{
	Sprite::init();




	return true;
}
void Item::setRowAndCol(int r ,int c)
{
	row = r;
	col = c;
}
void Item::initItem(int type ,int r,int c)
{
	this->type = type;
	this->row = r; 
	this->col	= c;
	setRowAndCol(r,c);
	char chitem [100];
	sprintf(chitem,"%d.png",type);
	Sprite* mitem = Sprite::create(chitem);
	this->addChild(mitem,2);
	mitem->setAnchorPoint(Point::ZERO);
	//this->setAnchorPoint(Point::ZERO);
}
int Item::getRow()const
{
	return row;
}
int Item::getCol()const
{
	return col;
}
void Item::setIsPass(bool bl)
{
	isPass = bl;
}
bool Item::getIsPass()const
{
	return isPass;
}
int Item::getType()const
{
	return type ;
}
void Item::startScaleAction()
{
	ScaleTo* toBig			=	ScaleTo::create(0.2f,0.8f);
	ScaleTo* toSmall		=	ScaleTo::create(0.2f,1.0f);
	Sequence* seq			=	Sequence::create(toBig,toSmall,NULL);
	RepeatForever* repeat	=	RepeatForever::create(seq);
	this->runAction(repeat);
}
void Item::stopScaleAction()
{
	this->stopAllActions();
	ScaleTo* toSmall		=	ScaleTo::create(0.2f,1.0f);
	this->runAction(toSmall);
}
void Item::disappear()
{
	ParticleSystemQuad* sys	=	ParticleSystemQuad::create("particleTexture.plist");
	this->addChild(sys);
	sys->setPosition(40,40);

	RemoveSelf* self		=	RemoveSelf::create();
	//¶¯×÷ÑÓÊ±
	DelayTime* delay		=	DelayTime::create(1.5f);
	Sequence* seq			=	Sequence::create(delay,self,NULL);

	this->runAction(seq);
}