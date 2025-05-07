#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"

class Stage
{
public:

	//������
	static constexpr int CREATES = 3;

	//�T�C�Y
	static constexpr VECTOR SCLAE = { 2.0f,2.0f,2.0f };

	//�����ʒu
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

	//�X�e�[�W
	Transform stages_[CREATES];

};

