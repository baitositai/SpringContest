#include "SkyDome.h"

SkyDome::SkyDome()
{
	state_ = STATE::NONE;

	// ��ԊǗ�
	stateChanges_.emplace(STATE::NONE, std::bind(&SkyDome::ChangeStateNone, this));
	stateChanges_.emplace(STATE::STAY, std::bind(&SkyDome::ChangeStateStay, this));
	stateChanges_.emplace(STATE::FOLLOW, std::bind(&SkyDome::ChangeStateFollow, this));
}

void SkyDome::Load()
{
	//���f���ݒ�
	SetModel();
}

void SkyDome::Init()
{
	// Z�o�b�t�@����(�˂������΍�)
	MV1SetUseZBuffer(transform_.modelId, false);
	MV1SetWriteZBuffer(transform_.modelId, false);

	// ��ԑJ��
	ChangeState(STATE::STAY);
}

void SkyDome::Update()
{
	// �X�V�X�e�b�v
	stateUpdate_();
}

void SkyDome::Draw()
{
	MV1DrawModel(transform_.modelId);
}

void SkyDome::SetModel()
{
	// ���f������̊�{���
	transform_.SetModel(
		ResourceManager::GetInstance().LoadModelDuplicate(
			ResourceManager::SRC::SKY_DOME));
	transform_.scl = SCALE;
	transform_.pos = Utility::VECTOR_ZERO;
	transform_.quaRot = Quaternion::Euler(
		0.0f,
		Utility::Deg2RadF(180.0f),
		0.0f
	);
	transform_.quaRotLocal = Quaternion();
	transform_.Update();
}

void SkyDome::ChangeState(STATE state)
{
	// ��ԕύX
	state_ = state;

	// �e��ԑJ�ڂ̏�������
	stateChanges_[state_]();
}

void SkyDome::ChangeStateNone()
{
	stateUpdate_ = std::bind(&SkyDome::UpdateNone, this);
}

void SkyDome::ChangeStateStay()
{
	stateUpdate_ = std::bind(&SkyDome::UpdateStay, this);
}

void SkyDome::ChangeStateFollow()
{
	stateUpdate_ = std::bind(&SkyDome::UpdateFollow, this);
	transform_.Update();
}

void SkyDome::UpdateNone()
{
}

void SkyDome::UpdateStay()
{
	//�X�J�C�h�[���̉�]����
	Quaternion yRot = Quaternion::AngleAxis(Utility::Deg2RadF(ROT_SPEED), Utility::AXIS_Y);
	transform_.quaRot = Quaternion::Mult(transform_.quaRot, yRot);
	transform_.Update();
}

void SkyDome::UpdateFollow()
{
	transform_.Update();
}
