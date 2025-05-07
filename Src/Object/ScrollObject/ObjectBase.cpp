#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ScrollManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/DataBank.h"
#include "../../Utility/Utility.h"
#include "../Character/Player.h"
#include "ObjectBase.h"

ObjectBase::ObjectBase()
	: resMng_(ResourceManager::GetInstance()),
	scnMng_(SceneManager::GetInstance())
{
	state_ = STATE::NONE;
	color_ = -1;
	radius_ = -1.0f;

	stateChanges_.emplace(STATE::NONE, std::bind(&ObjectBase::ChangeStateNone, this));
	stateChanges_.emplace(STATE::SCROLL, std::bind(&ObjectBase::ChangeStateScroll, this));
	stateChanges_.emplace(STATE::HIT, std::bind(&ObjectBase::ChangeStateHit, this));
}

void ObjectBase::Load(void)
{
	//�f�o�b�O�p�J���[
	color_ = 0xffff00;

	//���f���̏�����
	InitModel();

	//���y�̓ǂݍ���
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::ITEM_GET_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ITEM_GET_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::BLAST_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BLAST_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::ENEMY_DAMAGE_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ENEMY_DAMAGE_SE).handleId_);

}

void ObjectBase::Init()
{
	//���a�̐ݒ�
	radius_ = DEFAULT_RADIUS;

	//��ԑJ��
	ChangeState(STATE::NONE);
}

void ObjectBase::Update()
{
	// �X�V�X�e�b�v
	stateUpdate_();

	//�g�����X�t�H�[�����X�V
	transform_.Update();
}

void ObjectBase::Draw()
{
	if (state_ == STATE::NONE) { return; }	//��X�N���[����Ԃ̏ꍇ�`�悵�Ȃ�
}

void ObjectBase::Release()
{
	SoundManager::GetInstance().Stop(SoundManager::SOUND::ENEMY_DAMAGE_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::BLAST_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::ITEM_GET_SE);
}

void ObjectBase::ChangeState(STATE state)
{
	// ��ԕύX
	state_ = state;

	// �e��ԑJ�ڂ̏�������
	stateChanges_[state_]();
}

void ObjectBase::ChangeStateNone()
{
	stateUpdate_ = std::bind(&ObjectBase::UpdateNone, this);
}

void ObjectBase::ChangeStateScroll()
{
	//�ʒu�����߂�
	DecideRandPos();

	stateUpdate_ = std::bind(&ObjectBase::UpdateScroll, this);
}

void ObjectBase::ChangeStateHit()
{
	stateUpdate_ = std::bind(&ObjectBase::UpdateHit, this);
}

void ObjectBase::UpdateNone()
{
	//���̏�Ԃ̂Ƃ��͉������������Ȃ�
}

void ObjectBase::UpdateScroll()
{
	//�X�N���[��
	auto& scr = ScrollManager::GetInstance();
	//Z�l�����炵�Ă���
	transform_.pos.z -= scr.GetScrollSpeed(DataBank::GetInstance().Output().playerId_);
}

void ObjectBase::UpdateHit()
{
	//��Ԃ�ς���
	ChangeState(STATE::NONE);
}

void ObjectBase::DecideRandPos()
{
	// ������ X ���W������
	float posX = static_cast<float>(ScrollManager::MOVE_LIMIT_LEFT + GetRand(
		static_cast<int>(ScrollManager::MOVE_LIMIT_RIGHT - ScrollManager::MOVE_LIMIT_LEFT)));

	// Z ���W���Œ�l�Őݒ�
	transform_.pos = { posX, 0.0f, ScrollManager::SCROLL_START_LINE };
}
