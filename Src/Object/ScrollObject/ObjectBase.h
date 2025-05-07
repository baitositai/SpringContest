#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"
#include "../Character/Player.h"

class ResourceManager;
class SceneManager;

class ObjectBase
{

public:

	//通常半径
	static constexpr float DEFAULT_RADIUS = 20.0f;

	//爆発エフェクト相対座標
	static constexpr VECTOR EXPLOSION_POS = { 0.0f, 0.0f, 0.0f };

	enum class STATE
	{
		NONE,
		SCROLL,
		HIT,
	};

	// コンストラクタ
	ObjectBase();

	// デストラクタ
	~ObjectBase() = default;

	virtual void Load();
	virtual void Init();
	virtual void Update();
	virtual void Draw();	
	void Release();
	
	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="state"></param>次の状態
	void ChangeState(const STATE state);

	/// <summary>
	/// 衝突判定後の処理
	/// </summary>
	/// <param name="player"></param>プレイヤー
	virtual void OnCollision(Player& player) = 0;

	//トランスフォームを返す
	inline const Transform& GetTransform() const { return transform_; }

	//状態を返す
	inline const STATE& GetState()const { return state_; }

	//半径を返す
	inline const float& GetRadius()const { return radius_; }

protected:
	
	//状態
	STATE state_;

	//デバッグ用カラー
	int color_;

	//半径
	float radius_;

	// モデル制御の基本情報
	Transform transform_;	
	
	// シングルトン参照
	ResourceManager& resMng_;
	SceneManager& scnMng_;

private:

	// 状態管理(状態遷移時初期処理)
	std::map<STATE, std::function<void()>> stateChanges_;

	// 状態管理(更新ステップ)
	std::function<void()> stateUpdate_;

	// 状態遷移
	void ChangeStateNone();
	void ChangeStateScroll();
	void ChangeStateHit();

	// 更新ステップ
	void UpdateNone();
	void UpdateScroll();
	virtual void UpdateHit();

	//位置のランダム決定
	void DecideRandPos();

	//モデルの初期化処理
	virtual void InitModel() = 0;
};