#pragma once
#include "ObjectBase.h"

class LifeItem : public ObjectBase
{
public:

	//スケール
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//体力回復量
	static constexpr int LIFE_HEAL = 1;

	//スコア量
	static constexpr int SCORE = 100;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	LifeItem();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LifeItem();

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

