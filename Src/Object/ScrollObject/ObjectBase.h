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

	//状態
	enum class STATE
	{
		NONE,
		SCROLL,
		HIT,
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ObjectBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjectBase() = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	virtual void Load();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();	

	/// <summary>
	/// 解放
	/// </summary>
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

	/// <summary>
	/// トランスフォームを返す
	/// </summary>
	/// <returns></returns>
	inline const Transform& GetTransform() const { return transform_; }

	/// <summary>
	/// 状態を返す
	/// </summary>
	/// <returns></returns>状態
	inline const STATE& GetState()const { return state_; }

	/// <summary>
	/// 半径を返す
	/// </summary>
	/// <returns></returns>半径
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