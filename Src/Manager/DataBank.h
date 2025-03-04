#pragma once
#include "../Utility/StaticSingleton.h"
#include "SceneManager.h"

class DataBank : public StaticSingleton<DataBank>
{
public:

	struct SYSTEM_INFO
	{
		SceneManager::MODE mode_;	//�Q�[�����[�h
		bool autoTackle_;			//�^�b�N���̎�����
	};

	//����������
	void Init();

	//�f�[�^�����
	void Input(const SceneManager::MODE& mode);
	void Input(const bool& autoTackle);

	//�o��
	inline const SYSTEM_INFO& Output()const { return systemInfo_; }

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(DataBank);

	//�V�X�e�����
	SYSTEM_INFO systemInfo_;

	DataBank();
	~DataBank() = default;
};

