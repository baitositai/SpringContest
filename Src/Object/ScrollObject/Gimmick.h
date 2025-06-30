#pragma once
#include "ObjectBase.h"
#include "../../Utility/Utility.h"

class Gimmick : public ObjectBase
{
public:

	//スケール
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//ダメージ量
	static constexpr int DAMAGE = -1;

	//スコア量
	static constexpr int SCORE = -500;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Gimmick();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Gimmick();

	/// <summary>
	/// モデルの初期化
	/// </summary>
	void InitModel() override;

	/// <summary>
	/// 衝突後の処理処理
	/// </summary>
	/// <param name="player"></param>
	void OnCollision(Player& player) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

};
