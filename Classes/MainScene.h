#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void update(float f) override;
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*)override;
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*)override;
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

	CREATE_FUNC(MainScene);
private:
	cocos2d::Sprite* airplane1;
	cocos2d::Sprite* airplane2;
	cocos2d::DrawNode* mouse_rect;
	int state = 0;
	cocos2d::Vec2 touchPoint{500,500};
	float moveSpeed = 10.0;

	//EventListenerMouse* _mouseListener;
};



#endif

