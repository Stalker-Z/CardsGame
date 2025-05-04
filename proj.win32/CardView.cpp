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
	suit->setPosition(cocos2d::Vec2(front->getContentSize().width/2 + 50, front->getContentSize().height - 50)); // �Ϸ�Сͼ��
	front->addChild(suit);
	auto smallNum = Sprite::create(model->smallNumPath);
	smallNum->setScale(1.0f);
	smallNum->setPosition(cocos2d::Vec2(front->getContentSize().width/2 - 50, front->getContentSize().height - 50)); // �Ϸ�С����
	front->addChild(smallNum);
	auto bigNum = Sprite::create(model->bigNumPath);
	bigNum->setScale(1.0f);
	bigNum->setPosition(cocos2d::Vec2(front->getContentSize().width / 2, front->getContentSize().height / 2 - 20)); // �м������
	front->addChild(bigNum);

	CardView* view = new (std::nothrow) CardView(model, front, back);
	if (view) {
		view->autorelease(); // Cocos2d-x �Զ��ڴ����
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
	// �����¼������ӿ�������
	CCLOG("ONCLICK %d", int(this->getNum()));
	cocos2d::EventCustom event(CARD_CLICK_EVENT);
	event.setUserData(this); // ���ݵ�ǰ����ָ��

	// ��ȡȫ���¼��ַ���������
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
			if (this->getField() != CPT_BOTTOM && this->model->isSelectable) this->_onClick(); // �������
		}
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}