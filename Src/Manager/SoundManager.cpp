#include "SoundManager.h"

void SoundManager::Init()
{
	//初期化
	sounds_.clear();
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

	//一部の音声ファイルが再生中か調べる
	if (CheckSoundFile(sound)) { return; }

	//再生処理
	PlaySoundMem(sounds_[sound].data, sounds_[sound].playMode);
}

void SoundManager::Stop(const SOUND sound)
{
	//中身がない場合処理を行わない
	int ret = CheckSoundMem(sounds_[sound].data);
	if (ret == -1) { return; }
	//元データがないときは警告
	if (sounds_.find(sound) == sounds_.end())assert("設定していない音声を停止しようとしています。");
	StopSoundMem(sounds_[sound].data);
}

void SoundManager::AdjustVolume(const SOUND sound, const int persent)
{
	//元データがないときは警告
	if (sounds_.find(sound) == sounds_.end())assert("設定していない音声を設定しようとしています。");
	ChangeVolumeSoundMem(VOLUME_MAX * persent / 100, sounds_[sound].data);
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

bool SoundManager::CheckSoundFile(const SOUND snd)
{
	switch (snd)
	{
	case SOUND::CHANGE_SCENE_SE:
	case SOUND::JUMP_SE:
		//再生中か
		if (CheckSoundMem(sounds_[snd].data) == 1) { return true; }
		break;

	default:
		break;
	}

	return false;
}
