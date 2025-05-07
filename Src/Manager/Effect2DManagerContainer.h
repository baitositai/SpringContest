#pragma once
#include "../framework.h"
#include "../Common/Vector2.h"
#include "../Utility/StaticSingleton.h"
#include "SoundManager.h"

class Effect2DManager;

class Effect2DManagerContainer : public StaticSingleton<Effect2DManagerContainer>
{
public:

	//初期化処理
	void Init();

	//更新処理(プレイヤー分まとめて行う)
	void Update();

	//指定したプレイヤーのエフェクトマネージャーを取得
	Effect2DManager* GetManager(const int playerId);

private:

	std::unordered_map<int, std::unique_ptr<Effect2DManager>> managers_;

	//シングルトンの生成
	THIS_CLASS_IS_STATIC_SINGLETON(Effect2DManagerContainer);

	Effect2DManagerContainer();
	~Effect2DManagerContainer() = default;
};

