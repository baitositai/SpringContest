#include "SceneManager.h"
#include "ScrollManager.h"

ScrollManager::ScrollManager()
{
	Init();
}

void ScrollManager::Init()
{
	//������
	scrollSpeed_ = DEFAULRT_SCROLL_SPEED;
	step_ = 0.0f;
}

void ScrollManager::Update()
{
	step_ += SceneManager::GetInstance().GetDeltaTime();
	if ((int)step_ >= SPEED_UP_TIME) {
		step_ = 0.0f;				//������
		scrollSpeed_ += ACC_SPEED;	//���x�A�b�v
	}
}

void ScrollManager::ChangeScrollSpeed(const float speed)
{
	scrollSpeed_ += speed;
	
	//�Œᑬ�x�������Ȃ��悤�ɂ���
	if (scrollSpeed_ < DEFAULRT_SCROLL_SPEED) { scrollSpeed_ = DEFAULRT_SCROLL_SPEED; }
	//�ō����x������Ȃ��悤�ɂ���
	else if (scrollSpeed_ > MAX_SCROLL_SPEED) { scrollSpeed_ = MAX_SCROLL_SPEED; }
}
