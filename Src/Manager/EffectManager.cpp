#include "EffectManager.h"
#include "SoundManager.h"

void EffectManager::Init()
{
}

void EffectManager::Add(const EFFECT& efc, int data)
{
	//�A�z�z����ɂ��łɗv�f�������Ă��邩������
	//�����Ă����珈���I��
	if (effectRes_.find(efc) != effectRes_.end())return;

	//�V�K�f�[�^�̂��ߏ���ǉ�
	effectRes_.emplace(efc, data);
}

void EffectManager::Play(const EFFECT& efc, const VECTOR& pos, const Quaternion& qua, const float& size, const SoundManager::SOUND sound)
{
	//���f�[�^���Ȃ��Ƃ��͌x��
	if (effectRes_.find(efc) == effectRes_.end())assert("�ݒ肵�Ă��Ȃ��G�t�F�N�g���Đ����悤�Ƃ��Ă��܂��B");

	//�Đ��z����ɗv�f�������Ă��Ȃ���������
	if (effectPlay_.find(efc) == effectPlay_.end())
	{
		//�����Ă��Ȃ��Ƃ��v�f��ǉ�����
		effectPlay_.emplace(efc, PlayEffekseer3DEffect(effectRes_[efc]));
	}
	else
	{
		//�����Ă����猳�����ɏ㏑������
		effectPlay_[efc] = PlayEffekseer3DEffect(effectRes_[efc]);
	}

	//�e��ݒ蓯��
	SyncEffect(efc, pos, qua, size);

	//���ʉ��̍Đ�
	if (sound != SoundManager::SOUND::NONE) {
		SoundManager::GetInstance().Play(sound);
	} 
}

void EffectManager::Stop(const EFFECT& efc)
{
	//�z����ɓ����Ă��Ȃ����̂��~���悤�Ƃ�����x��
	if (effectPlay_.find(efc) == effectPlay_.end())assert("�ݒ肵�Ă��Ȃ��G�t�F�N�g���~���悤�Ƃ��Ă��܂��B");
	//�Đ���~
	StopEffekseer3DEffect(effectPlay_[efc]);
}

void EffectManager::SyncEffect(const EFFECT& efc, const VECTOR& pos, const Quaternion& qua, const float& size)
{
	//���̑��e��ݒ�
	//�傫��
	SetScalePlayingEffekseer3DEffect(effectPlay_[efc], size, size, size);
	//�p�x
	SetRotationPlayingEffekseer3DEffect(effectPlay_[efc], qua.ToEuler().x, qua.ToEuler().y, qua.ToEuler().z);
	//�ʒu
	SetPosPlayingEffekseer3DEffect(effectPlay_[efc], pos.x, pos.y, pos.z);
}

bool EffectManager::IsPlayEffect(const EFFECT& efc)
{
	if (effectPlay_[efc] == -1 || IsEffekseer3DEffectPlaying(effectPlay_[efc]) == -1)
	{
		return true;
	}
	return false;
}

void EffectManager::Destroy()
{
	//���X�̃f�[�^�̓��\�[�X�}�l�[�W���������Ă���̂ł����B
	effectRes_.clear();
}

EffectManager::EffectManager()
{
	Init();
}