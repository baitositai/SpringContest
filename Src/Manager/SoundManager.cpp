#include "SoundManager.h"

void SoundManager::Init()
{
}

void SoundManager::Add(const TYPE type, const SOUND sound, const int data)
{
	//�A�z�z����ɂ��łɗv�f�������Ă��邩������
	//�����Ă����珈���I��
	if (sounds_.find(sound) != sounds_.end())return;


	//�Đ�����Ƃ��f�[�^�̎�ނɂ����
	//���[�v�Đ����P�����𔻒f����
	int mode = -1;
	if (type == TYPE::BGM) mode = DX_PLAYTYPE_LOOP;
	else mode = DX_PLAYTYPE_BACK;

	//�V�K�f�[�^�̂��ߏ���ǉ�
	sounds_.emplace(sound, SoundData{ data,type ,mode });
}

void SoundManager::Play(const SOUND sound)
{
	//���f�[�^���Ȃ��Ƃ��͌x��
	if (sounds_.find(sound) == sounds_.end())assert("�ݒ肵�Ă��Ȃ��������Đ����悤�Ƃ��Ă��܂��B");

	//�Đ�����
	PlaySoundMem(sounds_[sound].data, sounds_[sound].playMode);
}

void SoundManager::Stop(const SOUND sound)
{
	//���f�[�^���Ȃ��Ƃ��͌x��
	if (sounds_.find(sound) == sounds_.end())assert("�ݒ肵�Ă��Ȃ��������~���悤�Ƃ��Ă��܂��B");
	StopSoundMem(sounds_[sound].data);
}

void SoundManager::AdjustVolume(const SOUND sound, const int persent)
{
	//���f�[�^���Ȃ��Ƃ��͌x��
	if (sounds_.find(sound) == sounds_.end())assert("�ݒ肵�Ă��Ȃ�������ݒ肵�悤�Ƃ��Ă��܂��B");
	ChangeVolumeSoundMem(255 * persent / 100, sounds_[sound].data);
}

void SoundManager::Destroy(void)
{
	//�z��v�f�P�폜
	sounds_.clear();
}

SoundManager::SoundManager()
{
	Init();
}
