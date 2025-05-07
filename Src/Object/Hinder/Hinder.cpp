#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ScoreBank.h"
#include "../../Manager/DataBank.h"
#include "Hinder.h"

Hinder::Hinder()
{
	imgHinder_ = -1;
	imgHinderGage_ = -1;
	imgItem_ = -1;
	imgItemGage_ = -1;
	isStart_ = false;
}

void Hinder::Load()
{
	//�摜�ǂݍ���
	ResourceManager& res = ResourceManager::GetInstance();
	imgHinder_ = res.Load(ResourceManager::SRC::HINDER).handleId_;
	imgHinderGage_ = res.Load(ResourceManager::SRC::HINDER_GAGE).handleId_;
}

void Hinder::Init()
{
}

void Hinder::Update()
{
	int playerId = DataBank::GetInstance().Output().playerId_;

	//�Q�[�W�X�V
	if (ScoreBank::GetInstance().GetScore(playerId) >= ACHIEVEMENT_SCORE)
	{
		//�A�C�e�����ʔ���
		isStart_ = true;

		//�X�R�A���Z�b�g
		ScoreBank::GetInstance().ResetScore(playerId);
	}
}

void Hinder::Draw()
{
	DrawRotaGraph(
		HINDER_GAGE_POS_X,
		HINDER_GAGE_POS_Y,
		1.0f,
		0.0f,
		imgHinderGage_,
		true,
		false);

	//�Q�[�W�̒����X�V
	float scoreMax = (float)ACHIEVEMENT_SCORE;
	float divSize = static_cast<float>(HINDER_SIZE_X / scoreMax);
	int barLength = static_cast<int>(divSize * ScoreBank::GetInstance().GetScore(SceneManager::GetInstance().GetScreenCount()));

	DrawExtendGraph(
		HINDER_POS_X,
		HINDER_POS_Y,
		HINDER_POS_X + barLength,
		HINDER_POS_Y + HINDER_SIZE_Y,
		imgHinder_,
		true);
}