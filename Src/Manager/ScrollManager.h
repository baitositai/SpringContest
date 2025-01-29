#pragma once
#include "../Utility/StaticSingleton.h"

class ScrollManager : public StaticSingleton<ScrollManager>
{
public:

	//通常スクロールスピード
	static constexpr float DEFAULRT_SCROLL_SPEED = 10.0f;

	ScrollManager();
	~ScrollManager();

	void Init();
	void Update();
	void Release();

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(ScrollManager);

	//スクロールスピード
	float scrollSpeed_;

};

