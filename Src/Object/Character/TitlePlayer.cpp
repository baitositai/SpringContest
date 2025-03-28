#include "TitlePlayer.h"
#include "../../Application.h"
#include "../../Manager/ResourceManager.h"
#include "../ScrollObject/ObjectBase.h"
#include"../../Utility/Utility.h"


TitlePlayer::TitlePlayer()
{
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Load(void)
{
	//���f���̏�����
	auto& res = ResourceManager::GetInstance();
	trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::PLAYER));
	trans_.scl = SCALE;
	trans_.pos = Utility::VECTOR_ZERO;
	trans_.pos.x = 500;
	trans_.pos.y = 100;
	trans_.pos.z = -100;
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal =
		Quaternion::Euler({ 0.0f, Utility::Deg2RadF(0.0f), 0.0f });
	trans_.Update();
}

void TitlePlayer::Init(void)
{
	//���ϐ��̏�����
	InitAnim();
}

void TitlePlayer::Update(void)
{
	trans_.Update();
	animController_->Update();

}

void TitlePlayer::Draw(void)
{
	//�`��
	MV1DrawModel(trans_.modelId);

	
}

void TitlePlayer::Release(void)
{
}

void TitlePlayer::InitAnim()
{
	//�A�j���[�V�����̏�����
	animController_ = std::make_unique<AnimationController>(trans_.modelId);
	std::string path = Application::PATH_MODEL + "Player/Animation/";
	animController_->Add((int)ANIM_TYPE::IDLE, path + "Idle.mv1", 10.0f);
	animController_->Add((int)ANIM_TYPE::DANCE, path + "Running.mv1", 40.0f);

	//�������
	animController_->Play((int)ANIM_TYPE::DANCE);
}
