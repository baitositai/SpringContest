#include "ScrollManager.h"

ScrollManager::ScrollManager()
{
	scrollSpeed_ = -1.0f;
}

void ScrollManager::Init()
{
	scrollSpeed_ = DEFAULRT_SCROLL_SPEED;
}

void ScrollManager::Update()
{
}

void ScrollManager::Release()
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
