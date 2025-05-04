#include "CardView.h"

CardView* CardView::create(CardModel* model)
{
	auto back = Sprite::create("card_general.png");
	back->setScale(1.0f);
	back->setPosition(0, 0);
	back->setVisible(false);

	auto front = Sprite::create("card_general.png");
	front->setScale(1.0f);
	front->setPosition(0, 0);
	front->setVisible(true);
	auto suit = Sprite::create(model->suitPath);
	suit->setScale(1.0f);
	suit->setPosition(cocos2d::Vec2(front->getContentSize().width/2 + 50, front->getContentSize().height - 50)); // 上方小图标
	front->addChild(suit);
	auto smallNum = Sprite::create(model->smallNumPath);
	smallNum->setScale(1.0f);
	smallNum->setPosition(cocos2d::Vec2(front->getContentSize().width/2 - 50, front->getContentSize().height - 50)); // 上方小数字
	front->addChild(smallNum);
	auto bigNum = Sprite::create(model->bigNumPath);
	bigNum->setScale(1.0f);
	bigNum->setPosition(cocos2d::Vec2(front->getContentSize().width / 2, front->getContentSize().height / 2 - 20)); // 中间大数字
	front->addChild(bigNum);

	CardView* view = new (std::nothrow) CardView(model, front, back);
	if (view) {
		view->autorelease(); // Cocos2d-x 自动内存管理
		return view;
	}
	CC_SAFE_DELETE(view);

	return view;
}

int CardView::getNum()
{
	return model->getFace();
}

cocos2d::Vec2 CardView::getPos()
{
	return model->position;
}

void CardView::setPos(cocos2d::Vec2 position)
{
	model->position = position;
}

CardPosType CardView::getField()
{
	return model->pos;
}

void CardView::setField(CardPosType field)
{
	model->pos = field;
}

int CardView::getCardId()
{
	return _cardId;
}

void CardView::_onClick() {
	// 创建事件并附加卡牌数据
	CCLOG("ONCLICK %d", int(this->getNum()));
	cocos2d::EventCustom event(CARD_CLICK_EVENT);
	event.setUserData(this); // 传递当前卡牌指针

	// 获取全局事件分发器并发送
	cocos2d::Director::getInstance()
		->getEventDispatcher()
		->dispatchEvent(&event);
}

void CardView::setupTouch() {
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](cocos2d::Touch* t, cocos2d::Event* e) { return true; };
	listener->onTouchEnded = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		CCLOG("%d", this->getCardId());
		cocos2d::Vec2 touchInLocal = this->convertTouchToNodeSpaceAR(t);
		touchInLocal.x += this->getContentSize().width / 2;
		touchInLocal.y += this->getContentSize().height / 2;
		cocos2d::Rect spriteRect(cocos2d::Vec2::ZERO, this->getContentSize());
		if (spriteRect.containsPoint(touchInLocal)) {;
			if (this->getField() != CPT_BOTTOM && this->model->isSelectable) this->_onClick(); // 触发点击
		}
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}