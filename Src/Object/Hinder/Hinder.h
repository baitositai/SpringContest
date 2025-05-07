#pragma once
#include "../../framework.h"
#include "../../Application.h"

class Hinder
{
public:
	
	//画像サイズ
	static constexpr int HINDER_SIZE_X = 180;
	static constexpr int HINDER_SIZE_Y = 68;

	//描画位置
	static constexpr int HINDER_GAGE_POS_X = Application::SCREEN_HALF_X - HINDER_SIZE_X / 2;
	static constexpr int HINDER_GAGE_POS_Y = 200;

	static constexpr int HINDER_POS_X = HINDER_GAGE_POS_X - HINDER_SIZE_X / 2;
	static constexpr int HINDER_POS_Y = HINDER_GAGE_POS_Y - HINDER_SIZE_Y / 2 + 20;

	//スコア獲得目安量
	static constexpr int ACHIEVEMENT_SCORE = 5000;


	Hinder();
	~Hinder() = default;

	void Load();
	void Init();
	void Update();
	void Draw();

	/// <summary>
	/// 妨害を開始判定を返す
	/// </summary>
	/// <returns></returns>妨害開始判定
	inline bool IsStart() const { return isStart_; }

	/// <summary>
	/// 妨害開始設定
	/// </summary>
	/// <param name="isStart"></param>妨害開始
	inline void SetStart(const bool isStart) { isStart_ = isStart; }

private:

	//画像読み込み
	int imgHinder_;
	int imgHinderGage_;
	int imgItem_;
	int imgItemGage_; 	
	
	//効果発動条件
	bool isStart_;
};

