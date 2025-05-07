#pragma once
#include "../Utility/StaticSingleton.h"
#include "SceneManager.h"

class DataBank : public StaticSingleton<DataBank>
{
public:

	struct SYSTEM_INFO
	{
		int playerId_;				//�v���C���[ID
		int playerNum_;				//�v���C���[�l��
		SceneManager::MODE mode_;	//�Q�[�����[�h
		bool autoTackle_;			//�^�b�N���̎�����
	};

	//����������
	void Init();

	/// <summary>
	/// �v���C���[�ԍ������(�v���C���[���Ƃŏ����𕪂���p)
	/// </summary>
	/// <param name="playerId"></param>�v���C���[�̔ԍ�
	void Input(const int& playerId);

	/// <summary>
	/// �v���C���[�l����ݒ�
	/// </summary>
	/// <param name="playerNum"></param>�l��
	void InputPlayNum(const int& playerNum);

	/// <summary>
	/// �Q�[�����[�h��ݒ�
	/// </summary>
	/// <param name="mode"></param>�Q�[�����[�h
	void Input(const SceneManager::MODE& mode);

	/// <summary>
	/// �����U���̐ݒ�
	/// </summary>
	/// <param name="autoTackle"></param>true�̏ꍇ����Afalse�̏ꍇ�Ȃ�
	void Input(const bool& autoTackle);

	/// <summary>
	/// �V�X�e������Ԃ�
	/// </summary>
	/// <returns></returns>�V�X�e�����
	inline const SYSTEM_INFO& Output()const { return systemInfo_; }

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(DataBank);

	//�V�X�e�����
	SYSTEM_INFO systemInfo_;

	DataBank();
	~DataBank() = default;
};

