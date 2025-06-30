#pragma once
#include "ObjectBase.h"

class PowerItem : public ObjectBase
{
public:

	//スケール
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//パワーの回復量
	static constexpr int POWER_HEAL = 1;

	//スコア量
	static constexpr int SCORE = 100;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PowerItem();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PowerItem();

	/// <summary>
	/// モデル初期化
	/// </summary>
	void InitModel() override;

	/// <summary>
	/// 衝突後の処理
	/// </summary>
	/// <param name="player"></param>プレイヤー
	void OnCollision(Player& player) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

};

