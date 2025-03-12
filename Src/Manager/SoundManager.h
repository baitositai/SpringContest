#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"

class SoundManager : public StaticSingleton<SoundManager>
{
public:

	//再生の種類分けするときに使う
	enum class TYPE 
	{
		NONE,
		BGM,
		SE
	};

	//サウンド
	enum class SOUND
	{
		NONE,
	};

	struct SoundData
	{
		int data;		//音声データ格納
		TYPE type;		//音声データの種類	※この要素は削除するかも
		int playMode;	//音声データの再生タイプ
	};

	//初期化
	void Init();

	//サウンドの追加
	void Add(const TYPE type, const SOUND sound, const int data);

	//音声データ
	void Play(const SOUND sound);

	//停止処理
	void Stop(const SOUND sound);

	//音量調節
	void AdjustVolume(const SOUND sound, const int persent);

	//解放
	void Destroy(void);

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(SoundManager);

	//データ格納用
	std::unordered_map<SOUND, SoundData>sounds_;

	SoundManager();
	~SoundManager() = default;

};

