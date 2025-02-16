#include "ScrollManager.h"

ScrollManager::ScrollManager()
{
	Init();
}

void ScrollManager::Init()
{
	scrollSpeed_ = DEFAULRT_SCROLL_SPEED;
}

void ScrollManager::Update()
{
}

float ScrollManager::GetScrollSpeed() const
{
	return scrollSpeed_;
}

void ScrollManager::ChangeScrollSpeed(const float speed)
{
	scrollSpeed_ += speed;
}
