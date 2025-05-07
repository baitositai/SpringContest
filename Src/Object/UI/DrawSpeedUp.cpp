#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/DataBank.h"
#include "../../Manager/SoundManager.h"
#include "../../Common/Fader.h"
#include "DrawSpeedUp.h"

DrawSpeedUp::DrawSpeedUp()
{
	state_ = STATE::NONE;
	img_ = -1;
	alpha_ = -1;
	rate_ = -1.0f;
	step_ = -1.0f;
}

void DrawSpeedUp::Load()
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::SPEED_UP).handleId_;

	SoundManager::GetInstance().Add(SoundManager::TYPE::SE,
		SoundManager::SOUND::SPEED_UP,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SPEED_UP_SE).handleId_);
}

void DrawSpeedUp::Init()
{
	//位置
	pos_ = { MARASON_POS_X,POS_Y };
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { pos_ = { VS_POS_X,POS_Y }; }

	//初期化
	alpha_ = 0;
	rate_ = 0.0f;
	step_ = MAINTAIN_TIME;
	ChangeState(STATE::NONE);
}

void DrawSpeedUp::Update()
{
	updateFunc_();
}

void DrawSpeedUp::Draw()
{
	if (state_ == STATE::NONE) { return; }

	//タイトルUI
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
	DrawRotaGraph(
		pos_.x,
		pos_.y,
		rate_,
		0.0f,
		img_,
		true,
		false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void DrawSpeedUp::Release()
{
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SPEED_UP);
}

void DrawSpeedUp::ChangeState(const STATE& state)
{
	state_ = state;

	switch (state_)
	{
	case STATE::NONE:
		updateFunc_ = std::bind(&DrawSpeedUp::UpdateStateNone, this);
		rate_ = 0.0f;
		alpha_ = (int)Fader::ALPHA_MAX;
		break;
	case STATE::EXPAND:
		updateFunc_ = std::bind(&DrawSpeedUp::UpdateStateExpand, this);
		//効果音の再生
		SoundManager::GetInstance().Play(SoundManager::SOUND::SPEED_UP);
		break;
	case STATE::MAINTAIN:
		updateFunc_ = std::bind(&DrawSpeedUp::UpdateStateMaintain, this);
		step_ = MAINTAIN_TIME;
		break;
	case STATE::TRANS:
		updateFunc_ = std::bind(&DrawSpeedUp::UpdateStateTrans, this);
		break;
	default:
		break;
	}
}

void DrawSpeedUp::UpdateStateNone()
{
}

void DrawSpeedUp::UpdateStateExpand()
{
	//拡大
	rate_ += RATE_SPEED;
	if (rate_ >= 1.0f)
	{
		rate_ = 1.0f;
		ChangeState(STATE::MAINTAIN);
	}
}

void DrawSpeedUp::UpdateStateMaintain()
{
	step_ -= SceneManager::GetInstance().GetDeltaTime();
	if (step_ <= 0.0f)
	{
		ChangeState(STATE::TRANS);
	}
}

void DrawSpeedUp::UpdateStateTrans()
{
	alpha_ -= static_cast<int>(Fader::SPEED_ALPHA);
	if (alpha_ <= 0)
	{
		alpha_ = 0;
		ChangeState(STATE::NONE);
	}
}
