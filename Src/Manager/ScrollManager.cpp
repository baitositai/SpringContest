#include "SceneManager.h"
#include "ScrollManager.h"

ScrollManager::ScrollManager()
{
	Init();
}

void ScrollManager::Init()
{
	//初期化
	scrollSpeed_ = DEFAULRT_SCROLL_SPEED;
	step_ = 0.0f;
}

void ScrollManager::Update()
{
	step_ += SceneManager::GetInstance().GetDeltaTime();
	if ((int)step_ >= SPEED_UP_TIME) {
		step_ = 0.0f;				//初期化
		scrollSpeed_ += ACC_SPEED;	//速度アップ
	}
}

void ScrollManager::ChangeScrollSpeed(const float speed)
{
	scrollSpeed_ += speed;
	
	//最低速度を下回らないようにする
	if (scrollSpeed_ < DEFAULRT_SCROLL_SPEED) { scrollSpeed_ = DEFAULRT_SCROLL_SPEED; }
	//最高速度を上回らないようにする
	else if (scrollSpeed_ > MAX_SCROLL_SPEED) { scrollSpeed_ = MAX_SCROLL_SPEED; }
}
