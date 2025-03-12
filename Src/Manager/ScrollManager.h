#pragma once
#include "../Utility/StaticSingleton.h"

class ScrollManager : public StaticSingleton<ScrollManager>
{
public:

	//最低スクロールスピード
	static constexpr float DEFAULRT_SCROLL_SPEED = 50.0f;

	//最高スクロールスピード
	static constexpr float MAX_SCROLL_SPEED = 50.0f;

	//加速
	static constexpr float ACC_SPEED = 2.0f;

	//減速
	static constexpr float DEC_SPEED = -2.0f;

	//移動制限
	static constexpr float MOVE_LIMIT_RIGHT = 250.0f;
	static constexpr float MOVE_LIMIT_LEFT = -250.0f;

	//地面
	static constexpr float GROUND = 0.0f;

	//スクロール開始ライン
	static constexpr float SCROLL_START_LINE = 600.0f;

	//スクロール終了ライン
	static constexpr float SCROLL_FINISH_LINE = -200.0f;

	//速度アップ時間
	static constexpr int SPEED_UP_TIME = 30;

	ScrollManager();
	~ScrollManager() = default;

	void Init();
	void Update();

	//スクロールスピードを返す
	inline const float GetScrollSpeed()const { return scrollSpeed_; }

	//スピードの変更
	void ChangeScrollSpeed(const float speed);

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(ScrollManager);

	//スクロールスピード
	float scrollSpeed_;

	//速度アップ用ステップ
	float step_;

};

