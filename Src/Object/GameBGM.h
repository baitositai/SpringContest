#pragma once
#include "../Manager/SoundManager.h"

class GameBGM
{
public:

	//��m���p�p�[�Z���g
	static constexpr int PERCENT = 3;

	//�傫��
	static constexpr int VOLUME = 70;

	GameBGM();
	~GameBGM() = default;

	void Load();
	void Init();
	void Release();	
	
	//��~
	void Stop();

private:

	//�T�E���h���
	SoundManager::SOUND soundType_;

};

