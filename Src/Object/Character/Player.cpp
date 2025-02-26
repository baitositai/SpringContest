#include "../../Utility/Utility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/ScrollManager.h"
#include "../../Manager/SceneManager.h"
#include "Player.h"

Player::Player()
{
	animationController_ = nullptr;
	state_ = STATE::NONE;
	aliveState_ = ALIVE_STATE::NONE;
	moveSpeed_ = -1.0f;
	isJump_ = false;
	stepJump_ = -1.0f;
	life_ = -1;
	pow_ = -1;
	radius_ = -1.0f;
	tackleTime_ = -1.0f;
	damageTime_ = -1.0f;

	stateChanges_.emplace(STATE::NONE, std::bind(&Player::ChangeStateNone, this));
	stateChanges_.emplace(STATE::ALIVE, std::bind(&Player::ChangeStateAlive, this));
	stateChanges_.emplace(STATE::DEATH, std::bind(&Player::ChangeStateDeath, this));

	aliveStateChanges_.emplace(ALIVE_STATE::RUN, std::bind(&Player::ChanageAliveStateRun, this));
	aliveStateChanges_.emplace(ALIVE_STATE::TACKLE, std::bind(&Player::ChanageAliveStateTackle, this));
	aliveStateChanges_.emplace(ALIVE_STATE::DAMAGE, std::bind(&Player::ChanageAliveStateDamage, this));
}

void Player::Load()
{
	// ���f���̊�{�ݒ�
	InitModel();

	//�A�j���[�V�����̐ݒ�
	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
}

void Player::Init()
{
	//�A�j���[�V�����̐ݒ�
	InitAnimation();

	//������
	moveSpeed_ = SPEED_MOVE;
	stepJump_ = 0.0f;
	pow_ = DEFAULT_POWER;
	life_ = DEFAULT_LIFE;
	radius_ = RADIUS;
	tackleTime_ = 0.0f;
	damageTime_ = 0.0f;

	//�������
	ChangeState(STATE::ALIVE);
	ChangeAliveState(ALIVE_STATE::RUN);
}

void Player::Update()
{
	// �X�V�X�e�b�v
	stateUpdate_();

	trans_.Update();

	animationController_->Update();
}

void Player::Draw()
{
	// ���f���̕`��
	MV1DrawModel(trans_.modelId);
}

void Player::AddLife(const int& life)
{
	life_ += life;

	//���C�t���ő�̎�
	if (life_ > DEFAULT_LIFE) {
		life_ = DEFAULT_LIFE;
	}
	//�v���C���[�̎��S����
	else if (life_ <= 0) {
		ChangeState(STATE::DEATH);
	}
}

void Player::AddPower(const int& pow)
{
	pow_ += pow;
	//�p���[���ő�̎�
	if (pow_ > DEFAULT_POWER) {
		pow_ = DEFAULT_POWER;
	}
}

void Player::ChangeAliveState(const ALIVE_STATE& state)
{
	aliveState_ = state;

	// �e��ԑJ�ڂ̏�������
	aliveStateChanges_[aliveState_]();
}

void Player::InitModel(void)
{
	trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(
		ResourceManager::SRC::PLAYER));
	trans_.scl = Utility::VECTOR_ONE;
	trans_.pos = Utility::VECTOR_ZERO;
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal =
		Quaternion::Euler({ 0.0f, Utility::Deg2RadF(180.0f), 0.0f });
	trans_.Update();
}

void Player::InitAnimation(void)
{
	std::string path = Application::PATH_MODEL + "Player/Animation/";
	animationController_->Add((int)ANIM_TYPE::IDLE, path + "Idle.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::RUN, path + "Running.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::TACKLE, path + "Tackle.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::JUMP, path + "Jump.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::DANCE, path + "Flair.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::DEATH, path + "Fall Flat.mv1", ANIM_SPEED);

	//�������
	animationController_->Play((int)ANIM_TYPE::RUN);
}

void Player::Process()
{
	auto& ins = InputManager::GetInstance();

	//����
	if (ins.IsNew(KEY_INPUT_A)) { trans_.pos.x -= moveSpeed_; }
	else if (ins.IsNew(KEY_INPUT_D)) { trans_.pos.x += moveSpeed_; }

	//�ړ�����
	float left = ScrollManager::MOVE_LIMIT_LEFT;
	float right = ScrollManager::MOVE_LIMIT_RIGHT;
	if (trans_.pos.x > right) { trans_.pos.x = right; }
	else if(trans_.pos.x < left) { trans_.pos.x = left; }

	//�W�����v����
	if (ins.IsTrgDown(KEY_INPUT_SPACE)) 
	{ 
		isJump_ = true; 
		if (aliveState_ != ALIVE_STATE::TACKLE ) { animationController_->Play((int)ANIM_TYPE::JUMP); }
	}
}

void Player::Jump(void)
{
	// �W�����v
	if (isJump_)
	{
		stepJump_ += SceneManager::GetInstance().GetDeltaTime() * JUMP_SPEED;
		trans_.pos.y = JUMP_HEIGHT * sin(RAD_PER_FRAME * stepJump_) + ScrollManager::GROUND;

		//�n�ʂɂ����Ƃ�
		if (trans_.pos.y <= 0)
		{
			trans_.pos.y = ScrollManager::GROUND;
			isJump_ = false;
			stepJump_ = 0.0f;
			animationController_->Play((int)ANIM_TYPE::RUN);
		}
	}
}

void Player::Run()
{
	//���ʏ����͂Ȃ�
}

void Player::Tackle()
{
	//���Ԃ����炷
	tackleTime_ -= SceneManager::GetInstance().GetDeltaTime();

	//���ԂɂȂ�����
	if (tackleTime_ <= 0.0f) {
		//�A�j���[�V������߂�
		animationController_->Play((int)ANIM_TYPE::RUN);
		//���Ԃ̏�����
		tackleTime_ = 0.0f;
		//�^�b�N�����I��
		ChangeAliveState(ALIVE_STATE::RUN);
	}
}

void Player::Damage()
{
	//���Ԃ����炷
	damageTime_ -= SceneManager::GetInstance().GetDeltaTime();

	//���f���̐F��ς���
	//MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
	if(static_cast<int>(damageTime_ * 10.0f) % 2 == 0) { MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f)); }
	else { MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f)); }

	//���ԂɂȂ�����
	if (damageTime_ <= 0.0f) {
		//���f���̐F��ʏ�ɖ߂�
		MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
		//���Ԃ̏�����
		damageTime_ = 0.0f;
		//�^�b�N�����I��
		ChangeAliveState(ALIVE_STATE::RUN);
	}
}

void Player::DebagDraw()
{
	DrawSphere3D(
	trans_.pos,
		radius_,
		20,
		0xff0000,
		0xff0000,
		true);

	//�f�o�b�O
	DrawFormatString(0, 0, 0x000000, "LIFE = %d", life_);
	DrawFormatString(0, 20, 0x000000, "POW = %d", pow_);
}

void Player::ChangeState(STATE state)
{
	// ��ԕύX
	state_ = state;

	// �e��ԑJ�ڂ̏�������
	stateChanges_[state_]();
}

void Player::ChangeStateNone(void)
{
	stateUpdate_ = std::bind(&Player::UpdateNone, this);
}

void Player::ChangeStateAlive(void)
{
	stateUpdate_ = std::bind(&Player::UpdateAlive, this);
}

void Player::ChangeStateDeath(void)
{
	stateUpdate_ = std::bind(&Player::UpdateDeath, this);

	//�A�j���[�V�������Đ�
	animationController_->Play((int)ANIM_TYPE::DEATH, false);
}

void Player::ChanageAliveStateRun()
{
	aliveStateUpdate_ = std::bind(&Player::Run, this);
}

void Player::ChanageAliveStateTackle()
{
	aliveStateUpdate_ = std::bind(&Player::Tackle, this);

	//�A�j���[�V�����̍Đ�
	animationController_->Play((int)ANIM_TYPE::TACKLE);
	
	//�^�b�N���̎��Ԑݒ�
	tackleTime_ = TACKLE_TIME;
}

void Player::ChanageAliveStateDamage()
{
	aliveStateUpdate_ = std::bind(&Player::Damage, this);

	damageTime_ = DAMAGE_TIME;
}

void Player::UpdateNone(void)
{
}

void Player::UpdateAlive(void)
{
	//���쏈��
	Process();

	// �W�����v����
	Jump();

	//������ԕʂ̍X�V
	aliveStateUpdate_();
}

void Player::UpdateDeath(void)
{
}
