#pragma once
#include "Stage.h"

class TitleStage : public Stage
{
public:

	//������
	static constexpr int TITLE_CREATE = 1;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TitleStage();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitleStage() override;

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	void Load() override;
};

