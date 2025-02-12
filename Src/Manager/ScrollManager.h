#pragma once
#include "../Utility/StaticSingleton.h"

class ScrollManager : public StaticSingleton<ScrollManager>
{
public:

	//通常スクロールスピード
	static constexpr float DEFAULRT_SCROLL_SPEED = 10.0f;

	//加速
	static constexpr float ACC_SPEED = 2.0f;

	//減速
	static constexpr float DEC_SPEED = -2.0f;

	ScrollManager();
	~ScrollManager() = default;

	void Init();
	void Update();
	void Release();

	//スクロールスピードを返す
	float GetScrollSpeed()const;

	//スピードの変更
	void ChangeScrollSpeed(const float speed);

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(ScrollManager);

	//スクロールスピード
	float scrollSpeed_;

};

