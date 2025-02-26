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

	//���Ԍo�ߗp�X�e�b�v
	float step_;
};

