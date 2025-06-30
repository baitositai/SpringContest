#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"

class Stage
{
public:

	//生成数
	static constexpr int CREATES = 3;

	//サイズ
	static constexpr VECTOR SCLAE = { 2.0f,2.0f,2.0f };

	//初期位置
	static constexpr VECTOR DEFAULT_POS[CREATES] = {
		{-2100,-2000,16000},
		{-2100,-2000,23000},
		{-2100,-2000,30000}
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stage();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Stage();

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

protected:

	//ステージ
	std::vector<Transform> stages_;

};

