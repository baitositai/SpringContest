#pragma once
#include "../Manager/SoundManager.h"

class GameBGM
{
public:

	//��m���p�p�[�Z���g
	static constexpr int PERCENT = 3;

	//�傫��
	static constexpr int VOLUME = 70;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameBGM();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameBGM() = default;

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	void Load();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// ���
	/// </summary>
	void Release();	
	
	/// <summary>
	/// ���y��~
	/// </summary>
	void Stop();

private:

	//�T�E���h���
	SoundManager::SOUND soundType_;

};

