#include "SoundManager.h"

void SoundManager::Init()
{
}

void SoundManager::Add(const TYPE type, const SOUND sound, const int data)
{
	//連想配列内にすでに要素が入っているかを検索
	//入っていたら処理終了
	if (sounds_.find(sound) != sounds_.end())return;


	//再生するときデータの種類によって
	//ループ再生か単発かを判断する
	int mode = -1;
	if (type == TYPE::BGM) mode = DX_PLAYTYPE_LOOP;
	else mode = DX_PLAYTYPE_BACK;

	//新規データのため情報を追加
	sounds_.emplace(sound, SoundData{ data,type ,mode });
}

void SoundManager::Play(const SOUND sound)
{
	//元データがないときは警告
	if (sounds_.find(sound) == sounds_.end())assert("設定していない音声を再生しようとしています。");

	//再生処理
	PlaySoundMem(sounds_[sound].data, sounds_[sound].playMode);
}

void SoundManager::Stop(const SOUND sound)
{
	//元データがないときは警告
	if (sounds_.find(sound) == sounds_.end())assert("設定していない音声を停止しようとしています。");
	StopSoundMem(sounds_[sound].data);
}

void SoundManager::AdjustVolume(const SOUND sound, const int persent)
{
	//元データがないときは警告
	if (sounds_.find(sound) == sounds_.end())assert("設定していない音声を設定しようとしています。");
	ChangeVolumeSoundMem(255 * persent / 100, sounds_[sound].data);
}

void SoundManager::Destroy(void)
{
	//配列要素善削除
	sounds_.clear();
}

SoundManager::SoundManager()
{
	Init();
}
