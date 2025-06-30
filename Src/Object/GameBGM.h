#pragma once
#include "../Manager/SoundManager.h"

class GameBGM
{
public:

	//低確率用パーセント
	static constexpr int PERCENT = 3;

	//大きさ
	static constexpr int VOLUME = 70;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameBGM();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameBGM() = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 解放
	/// </summary>
	void Release();	
	
	/// <summary>
	/// 音楽停止
	/// </summary>
	void Stop();

private:

	//サウンド種類
	SoundManager::SOUND soundType_;

};

