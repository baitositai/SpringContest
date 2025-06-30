#pragma once
#include "../../framework.h"
#include "../../Manager/SceneManager.h"
#include "Hinder.h"
#include "HinderObject.h"

class Hinder;
class HinderObject;

class HinderManager
{
public:

	//追加量
	static constexpr int ADD_OBJS = 2;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HinderManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HinderManager() = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	//邪魔
	std::unique_ptr<Hinder> hinders_[SceneManager::PLAYER_MAX];
	std::unique_ptr<HinderObject> objs_[SceneManager::PLAYER_MAX];

	//妨害を受けるか調べる
	void CheckHinder();

};

