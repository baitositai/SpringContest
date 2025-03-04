#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Utility/Utility.h"
#include "../Object/Stage/StageBase.h"
#include "../Object/Stage/StageDefault.h"


GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);
}

void GameScene::Load(void)
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂�true�ɂ���
	SetUseASyncLoadFlag(true);

	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

	//�J����
	mainCamera->ChangeMode(Camera::MODE::FIXED_POINT);

	//�X�e�[�W�̏�����
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Release();
		delete stages_[i];
	}

	stages_.clear();

	//������
	stageSpawnCounter_ = 0;
	stageSpawn_ = 0;
}

void GameScene::Init(void)
{

}

void GameScene::Update(InputManager& input)
{
	updataFunc_(input);
	return;
}

void GameScene::Draw(void)
{
	drawFunc_();
	return;
}

void GameScene::Release(void)
{
	//�t�H���g�폜
	DeleteFontToHandle(loadFont_);

	for (auto& stage : stages_) {
		stage->Release();
	}
}

void GameScene::LoadingUpdate(InputManager& ins)
{
	bool loadTimeOver = Utility::IsTimeOver(loadingTime_, LOADING_TIME);

	//���[�h���������������f
	if (GetASyncLoadNum() == 0 && loadTimeOver)
	{
		//�񓯊������𖳌��ɂ���
		SetUseASyncLoadFlag(false);

		//����������
		Init();

		//�t�F�[�h�C���J�n
		sceneManager_.StartFadeIn();

		//�X�V�֐��̃Z�b�g
		updataFunc_ = [&](InputManager& input) {NormalUpdate(input); };
		
		//�`��֐��̃Z�b�g
		drawFunc_ = std::bind(&GameScene::NormalDraw, this);
	}
}

void GameScene::NormalUpdate(InputManager& ins)
{

	//�X�e�[�W�̍X�V�����͓��I�z��ŉ�
	//�o�����Ă���A�C�e���͂��ׂčX�V����
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Update();

	}

	//�X�e�[�W�̏o���J�E���g�𑝂₷
	++stageSpawnCounter_;

	//�o���J�E���g���w��l�𒴂�����
	if (stageSpawn_ < 3)
	{

		stageSpawnCounter_ = 0;

		//�X�e�[�W�𓮓I����
		//�|�C���^�ɉ��������Ȃ������ݒ肷��Ƃ���
		//nullptr�����悤����
		StageBase* newStage = nullptr;

		//�X�e�[�W�̐���
		int stageTypeMaxNum = static_cast<int>(StageBase::STAGE_TYPE::MAX) - 1;

		//�X�e�[�W�̃^�C�v�������_���Ō��肷��
		int newStageType = GetRand(stageTypeMaxNum);

		//enmu�Ŏg�p���邽�߂ɃX�e�[�W�̃^�C�v�ɖ߂�
		StageBase::STAGE_TYPE randType = static_cast<StageBase::STAGE_TYPE>(newStageType);

		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			newStage = new StageDefault();
			break;
		}

		newStage->Init();

		//�o�����W
		VECTOR spawnPos;

		//���[�j���O����̂��߂Ɉ�U������
		spawnPos.x = 0;
		spawnPos.y = 0;
		spawnPos.z = 0;



		//�o���ʒu�ݒ�
		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			if (sSize == 0)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000;
			}
			if (sSize == 1)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000 + StageBase::SIZE_Z;
			}
			if (sSize == 2)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000 + StageBase::SIZE_Z * 2;
			}


			break;
		}


		//���W�̐ݒ�
		newStage->SetPos(spawnPos);

		//���I�z��ɒǉ�
		stages_.push_back(newStage);

		stageSpawn_++;

	}

	//�V�[���J��
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().
			ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameScene::LoadingDraw(void)
{
	//�unow loading�v�̕`��
	DrawNowLoading();
}

void GameScene::NormalDraw(void)
{
	//�f�o�b�O�`��
	DebagDraw();

	//�X�e�[�W�̕`������I�z��ł܂킷�`�ɕύX
	//�o�����Ă���A�C�e�����ׂĂ�`�悷��
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Draw();
	}


}

void GameScene::DebagDraw()
{
	////�f�o�b�O�n�̕`��͂����ɏ���
	DrawBox(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0xfff000,
		true);
}
