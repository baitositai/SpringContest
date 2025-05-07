#include "SceneManager.h"
#include "DataBank.h"
#include "ScrollManager.h"

ScrollManager::ScrollManager()
{
	Init();
}

void ScrollManager::Init()
{
	//初期化
	step_ = 0.0f;

	//すコロール速度の初期化
	scrollSpeed_.clear();

	//プレイヤーの数だけスクロールスピードを確保
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		scrollSpeed_.resize(SceneManager::PLAYER_MAX, DEFAULRT_SCROLL_SPEED);
	}
	else
	{
		scrollSpeed_.emplace_back(DEFAULRT_SCROLL_SPEED);
	}
}

void ScrollManager::ChangeScrollSpeed(const int playerId, const float speed)
{
	scrollSpeed_[playerId] += speed;
	
	//最低速度を下回らないようにする
	if (scrollSpeed_[playerId] < DEFAULRT_SCROLL_SPEED)
	{ 
		scrollSpeed_[playerId] = DEFAULRT_SCROLL_SPEED; 
	}

	//最高速度を上回らないようにする
	else if (scrollSpeed_[playerId] > MAX_SCROLL_SPEED) 
	{ 
		scrollSpeed_[playerId] = MAX_SCROLL_SPEED; 
	}
}
