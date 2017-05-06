#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainScene::create();

	scene->addChild(layer);
	
	return scene;
}

bool MainScene::init()
{
	if( !Layer::init() )
		return false;


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto label = Label::createWithTTF("世界,你好", "fonts/SIMLI.TTF", 24);
	label->setColor(Color3B::RED);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label,0);
	airplane1 = Sprite::create("Picture/airplane.png");
	airplane2 = Sprite::create("Picture/airplane.png");
//	 auto airplane = Sprite::create("Picture/airplane.png");

	airplane1->setScale(0.1, 0.1);
	airplane1->setPosition(200, 200);
	airplane1->setTag(12);
	airplane2->setScale(0.1, 0.1);
	airplane2->setPosition(100, 100);
	airplane2->setTag(13);
	this->addChild(airplane1, 1);
	this->addChild(airplane2, 1);
	

	this->schedule(schedule_selector(MainScene::update));


	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listen->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	listen->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	listen->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);

	return true;

}

void MainScene::update(float f)
{
//	
//	auto sp = this->getChildren();//获取这个层中所有的孩子,也就是所有的精灵，看不懂？别逗我了，点进去看源码吧，注意它的返回值类型。  
//	for (auto a : sp)
//	{
//		if(a->getBoundingBox().containsPoint(touchPoint))
//			continue;
//		auto esp = Point(touchPoint.x - a->getPosition().x, touchPoint.y - a->getPosition().y).getNormalized();
//		a->setPosition(a->getPosition()+esp*moveSpeed);
//		
//	}
	if (airplane1->getBoundingBox().containsPoint(touchPoint))
		return;
	if (airplane2->getBoundingBox().containsPoint(touchPoint))
		return;
	if (state == 1)
	{
		auto esp = (touchPoint - airplane1->getPosition()).getNormalized();
		airplane1->setPosition(airplane1->getPosition() + esp*moveSpeed);
	}
	if (state == 2)
	{
		auto esp = (touchPoint - airplane2->getPosition()).getNormalized();
		airplane2->setPosition(airplane2->getPosition() + esp*moveSpeed);
	}

	log("touch point:%f,%f",touchPoint.x,touchPoint.y);
}

bool MainScene::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event*)
{
	this->touchPoint = pTouch->getLocation();
	Point touch = pTouch->getLocation();//返回点击的位置

	if (airplane1->getBoundingBox().containsPoint(touch))
	{
		state = 1;
		return true;
	}

	if (airplane2->getBoundingBox().containsPoint(touch))
	{
		state = 2;
		return true;
	}
	
	this->mouse_rect = DrawNode::create();
	this->addChild(this->mouse_rect,2);

	return true;
}

void MainScene::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	auto airplane = getChildByTag(12);
	Point touch = pTouch->getLocation();//返回点击的位置  
	Rect rectPlayer = airplane->getBoundingBox();//看返回值类型，应该知道这个是飞机所占矩形区域的大小  

	if (rectPlayer.containsPoint(touch)) {//如果点击的点在这个矩形区域内就可以对飞机进行拖动  
		Point temp = pTouch->getDelta();
		airplane->setPosition(airplane->getPosition() + temp);
	}

	//
	this->mouse_rect->clear();
	Vec2 mouse_rect_points[4];
	mouse_rect_points[0] = this->touchPoint;
	mouse_rect_points[1] = Vec2(this->touchPoint.x, touch.y);
	mouse_rect_points[2] = touch;
	mouse_rect_points[3] = Vec2(touch.x, this->touchPoint.y);

	//绘制空心多边形
	//填充颜色：Color4F(1, 0, 0, 0), 透明
	//轮廓颜色：Color4F(0, 1, 0, 1), 绿色
	this->mouse_rect->drawPolygon(mouse_rect_points, 4, Color4F(1, 0, 0, 0), 1, Color4F(0, 1, 0, 1));
	//
}

void MainScene::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	this->removeChild(this->mouse_rect);
}