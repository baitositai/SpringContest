#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"

class ResourceManager;
class SceneManager;

class ObjectBase
{

public:

	//通常半径
	static constexpr float DEFAULT_RADIUS = 20.0f;

	enum class STATE
	{
		NONE,
		SCROLL,
		HIT,
	};

	// コンストラクタ
	ObjectBase(void);

	// デストラクタ
	~ObjectBase(void);

	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);	
	
	//状態変更
	void ChangeState(STATE state);

	//衝突判定後の処理
	virtual void OnCollision(Player& player) = 0;

	//トランスフォームを返す
	inline const Transform& GetTransform(void) const { return transform_; }

	//状態を返す
	inline const STATE& GetState()const { return state_; }

	//半径を返す
	inline const float& GetRadius()const { return radius_; }

protected:

	//デバッグ用カラー
	int color_;

	//半径
	float radius_;

public:

	//状態
	STATE state_;

	// 状態管理(状態遷移時初期処理)
	std::map<STATE, std::function<void(void)>> stateChanges_;

	// 状態管理(更新ステップ)
	std::function<void(void)> stateUpdate_;

	// シングルトン参照
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// モデル制御の基本情報
	Transform transform_;

	// 状態遷移
	void ChangeStateNone(void);
	void ChangeStateScroll(void);
	void ChangeStateHit(void);

	// 更新ステップ
	void UpdateNone(void);
	void UpdateScroll(void);
	void UpdateHit(void);

	//位置のランダム決定
	void DecideRandPos();
};