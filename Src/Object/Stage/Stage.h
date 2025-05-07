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

	Stage();
	~Stage();

	void Load();
	void Init();
	void Update();
	void Draw();

private:

	//ステージ
	Transform stages_[CREATES];

};

