#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ScrollManager.h"
#include "../Character/Player.h"
#include "ObjectBase.h"

ObjectBase::ObjectBase(void)
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

ObjectBase::~ObjectBase(void)
{
}

void ObjectBase::Load(void)
{
	color_ = 0xffff00;
}

void ObjectBase::Init(void)
{
	//���a�̐ݒ�
	radius_ = DEFAULT_RADIUS;

	//��ԑJ��
	ChangeState(STATE::NONE);
}

void ObjectBase::Update(void)
{
	// �X�V�X�e�b�v
	stateUpdate_();

	transform_.Update();
}

void ObjectBase::Draw(void)
{
	if (state_ == STATE::NONE) { return; }
	DrawSphere3D(transform_.pos, 20.0f, 10, color_, color_, true);
}

void ObjectBase::ChangeState(STATE state)
{
	// ��ԕύX
	state_ = state;

	// �e��ԑJ�ڂ̏�������
	stateChanges_[state_]();
}

void ObjectBase::OnCollision(Player& player)
{
}

void ObjectBase::ChangeStateNone(void)
{
	stateUpdate_ = std::bind(&ObjectBase::UpdateNone, this);
}

void ObjectBase::ChangeStateScroll(void)
{
	//�ʒu�����߂�
	DecideRandPos();

	stateUpdate_ = std::bind(&ObjectBase::UpdateScroll, this);
}

void ObjectBase::ChangeStateHit(void)
{
	stateUpdate_ = std::bind(&ObjectBase::UpdateHit, this);
}

void ObjectBase::UpdateNone(void)
{
}

void ObjectBase::UpdateScroll(void)
{
	//�X�N���[��
	auto& scr = ScrollManager::GetInstance();
	transform_.pos.z -= scr.GetScrollSpeed();
}

void ObjectBase::UpdateHit(void)
{
	//��Ԃ�ς���
	ChangeState(STATE::NONE);
}

void ObjectBase::DecideRandPos()
{
	// ������ X ���W������
	float posX = ScrollManager::MOVE_LIMIT_LEFT + GetRand(ScrollManager::MOVE_LIMIT_RIGHT - ScrollManager::MOVE_LIMIT_LEFT);

	// Z ���W���Œ�l�Őݒ�
	transform_.pos = { posX, 0.0f, ScrollManager::SCROLL_START_LINE };
}
