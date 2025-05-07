#pragma once
#include "../Manager/SoundManager.h"

class GameBGM
{
public:

	//低確率用パーセント
	static constexpr int PERCENT = 3;

	//大きさ
	static constexpr int VOLUME = 70;

	GameBGM();
	~GameBGM() = default;

	void Load();
	void Init();
	void Release();	
	
	//停止
	void Stop();

private:

	//サウンド種類
	SoundManager::SOUND soundType_;

};

