#pragma once
#include "../framework.h"
#include "../Application.h"
#include "../Manager/SceneManager.h"

class TimeCount
{
public:

	TimeCount();
	~TimeCount() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

private:

	//時間経過用ステップ
	float step_;
};

