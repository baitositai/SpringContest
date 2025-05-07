#include "Effect2DManager.h"
#include "../Utility/Utility.h"

Effect2DManager::Effect2DManager()
{
	//�f�[�^�̏�����
	effects_.clear();
}

void Effect2DManager::Update()
{
	//���g���Ȃ��ꍇ�������I����
	if (effects_.empty()) { return; }

	//�A�j���[�V�����X�V
	for (auto it = effects_.begin(); it != effects_.end(); ++it) 
	{
		//�A�j���[�V�������Đ��ς݂�
		if (!it->second.isPlay_)
		{ 
			continue;//�Đ����ĂȂ��ꍇ����
		}	
		//�X�V����
		it->second.step_++;

		//�A�j���[�V�����ԍ��̃A�^�b�`
		it->second.animNum_ = static_cast<int>(it->second.step_ / it->second.animSpeed_) % it->second.animMax_;

		//�A�j���[�V�����̏I���m�F
		if (it->second.animNum_ >= it->second.animMax_ - 1) { Stop(it->first); }
	}
}

void Effect2DManager::Add(const EFFECT& efc, int* image, const int& animMax, const float & animSpeed)
{	
	//�G�t�F�N�g�f�[�^
	Efc data = { image, animMax,0,animSpeed, Utility::VECTOR_ZERO, 1.0f,0.0f,0.0f,false };

	//�A�z�z����ɂ��łɗv�f�������Ă��邩������
	//�����Ă����珈���I��
	if (effects_.find(efc) != effects_.end()) { return; }

	//�V�K�f�[�^�̂��ߏ���ǉ�
	effects_.emplace(efc, data);
}

void Effect2DManager::Play(const EFFECT& efc, const VECTOR& pos, const float& rate, const float& angle, const SoundManager::SOUND& sound)
{
	//���f�[�^���Ȃ��Ƃ��͌x��
	if (effects_.find(efc) == effects_.end())assert("�ݒ肵�Ă��Ȃ��G�t�F�N�g���Đ����悤�Ƃ��Ă��܂��B");

	//�Đ������m�F
	if (effects_[efc].isPlay_) { Stop(efc); }	//�Đ����̏ꍇ�͏����������Ă���Đ�����

	//�Đ��J�n
	effects_[efc].isPlay_ = true;

	//�e��ݒ蓯��
	Sync(efc, pos, rate, angle);

	//���ʉ��̍Đ�
	if (sound != SoundManager::SOUND::NONE)
	{
		SoundManager::GetInstance().Play(sound);
	}
}

void Effect2DManager::Sync(const EFFECT& efc, const VECTOR& pos, const float& rate, const float& angle)
{
	effects_[efc].pos_ = pos;
	effects_[efc].rate_ = rate;
	effects_[efc].angle_ = angle;
}

void Effect2DManager::Stop(const EFFECT& efc)
{
	//�Đ���~
	effects_[efc].isPlay_ = false;

	//��������������
	effects_[efc].pos_ = Utility::VECTOR_ZERO;
	effects_[efc].rate_ = 1.0f;;
	effects_[efc].angle_ = 0.0f;
	effects_[efc].step_ = 0.0f;
	effects_[efc].animNum_ = 0;
}

void Effect2DManager::Destroy()
{
	//�f�[�^�̏�����
	effects_.clear();
}

void Effect2DManager::DrawScreenEffect(const EFFECT& efc)
{
	//�Đ������m�F
	if (!effects_[efc].isPlay_) { return; }

	//�X�N���[�����W�ɂ���
	VECTOR pos = ConvWorldPosToScreenPos(effects_[efc].pos_);

	DrawRotaGraph(
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		effects_[efc].rate_,
		effects_[efc].angle_,
		effects_[efc].image_[effects_[efc].animNum_],
		true,
		false);
}

void Effect2DManager::DrawBillboard(const EFFECT& efc)
{
	//�Đ������m�F
	if (!effects_[efc].isPlay_) { return; }

	DrawBillboard3D(
		effects_[efc].pos_,
		CENTER, CENTER,
		effects_[efc].rate_,
		0.0f,
		effects_[efc].image_[(int)effects_[efc].animNum_],
		true,
		false);
}
