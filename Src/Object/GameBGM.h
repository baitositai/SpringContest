#pragma once
#include "../Manager/SoundManager.h"

class GameBGM
{
public:

	static constexpr int PERCENT = 3;
	static constexpr int VOLUME = 70;

	GameBGM();
	~GameBGM();

	void Load();
	void Init();
	void Stop();

private:

	SoundManager::SOUND soundType_;

};

