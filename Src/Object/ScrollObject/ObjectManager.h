#pragma once
#include "../../framework.h"
#include "ObjectBase.h"

class ObjectBase;

class ObjectManager
{
public:

	//スクロールの間隔秒数
	static constexpr float INTERVEL_SECOND_MIN = 1.0f;
	static constexpr float INTERVEL_SECOND_MAX = 2.0f;

	//各種オブジェクト生成数
	static constexpr int ENEMY_CREATE_CNT = 4;
	static constexpr int GIMIC_CREATE_CNT = 2;
	static constexpr int LIFE_CREATE_CNT = 1;
	static constexpr int POW_CREATE_CNT = 1;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ObjectManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjectManager() = default;

	/// <summary>
	/// 読みこみ
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

	/// <summary>
	/// 解放
	/// </summary>
	void Release();

	/// <summary>
	/// オブジェクト配列を返す
	/// </summary>
	/// <returns></returns>オブジェクト配列
	inline const std::vector<std::unique_ptr<ObjectBase>>& GetObjects() const { return objs_; }

private:

	//スクロール開始用ステップ
	float step_;

	//オブジェクト
	std::vector<std::unique_ptr<ObjectBase>> objs_;

	//スクロールの開始
	void ScrollStart();

	//次回のスクロール開始秒数
	float NextStartSecond();

};

