#pragma once
#include "../../framework.h"
#include "../../Application.h"
#include "../../Common/Vector2.h"

class DrawSpeedUp
{
public:

	//描画位置(マラソン)
	static constexpr int MARASON_POS_X = Application::SCREEN_HALF_X;
	static constexpr int VS_POS_X = Application::SCREEN_HALF_X / 2;
	static constexpr int POS_Y = 200;

	//維持時間
	static constexpr float MAINTAIN_TIME = 1.5f;

	//拡大速度
	static constexpr float RATE_SPEED = 0.05f;

	enum class STATE
	{
		NONE,		//なし
		EXPAND,		//拡大
		MAINTAIN,	//維持
		TRANS		//消える
	};

	DrawSpeedUp();
	~DrawSpeedUp() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

	//状態変更
	void ChangeState(const STATE& state);

private:

	//状態
	STATE state_;

	//画像
	int img_;

	//アルファ地
	int alpha_;

	//拡大率
	float rate_;

	//ステップ
	float step_;

	//描画位置
	Vector2 pos_;

	//状態別更新
	std::function<void()> updateFunc_;

	//状態別更新処理
	void UpdateStateNone();
	void UpdateStateExpand();
	void UpdateStateMaintain();
	void UpdateStateTrans();

};

