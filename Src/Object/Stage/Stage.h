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

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Stage();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Stage();

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	virtual void Load();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

protected:

	//�X�e�[�W
	std::vector<Transform> stages_;

};

