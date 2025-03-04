#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/DataBank.h"
#include "../Manager/ScrollManager.h"
#include "../Utility/Utility.h"
<<<<<<< HEAD
#include "../Object/Character/Player.h"
#include "../Object/ScrollObject/ObjectManager.h"
#include "../Object/TimeCount.h"
=======
#include "../Object/Stage/StageBase.h"
#include "../Object/Stage/StageDefault.h"

>>>>>>> 2e3f2a964f8ab0512986127c62e45d1b4ceef81b

GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);

	players_.clear();
	objs_.clear();
	state_ = STATE::START;
	strCnt_ = -1.0f;
	playNum_ = -1;

	stateChanges_.emplace(STATE::START, std::bind(&GameScene::ChangeStart, this));
	stateChanges_.emplace(STATE::PLAY, std::bind(&GameScene::ChangePlay, this));
	stateChanges_.emplace(STATE::REZALT, std::bind(&GameScene::ChangeRezalt, this));
}

void GameScene::Load(void)
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂�true�ɂ���
	SetUseASyncLoadFlag(true);

	//�l���ݒ�
	playNum_ = 1;
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { playNum_ = SceneManager::PLAYER_MAX; }

	//�v���C���[
	for (int i = 0; i < playNum_; i++) {
		auto player = std::make_shared<Player>();
		player->Load();
		players_.emplace_back(std::move(player));
	}

	//�I�u�W�F�N�g
	for (int i = 0; i < playNum_; i++) {
		auto objs = std::make_unique<ObjectManager>();
		objs->Load();
		objs_.emplace_back(std::move(objs));
	}

	//����
	time_ = std::make_unique<TimeCount>();
	time_->Load();

	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

<<<<<<< HEAD
	//�J�����̐ݒ�
	auto cameras = SceneManager::GetInstance().GetCameras();
	for (int i = 0; i < cameras.size(); i++)
	{
		cameras[i]->ChangeMode(Camera::MODE::FIXED_POINT);
		cameras[i]->SetTargetPos(LOCAL_CAMERA_POS);
	}
=======
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
>>>>>>> 2e3f2a964f8ab0512986127c62e45d1b4ceef81b
}

void GameScene::Init(void)
{
	//�v���C���[������
	for (int i = 0; i < playNum_; i++) { 
		players_[i]->Init(); 
		players_[i]->SetKey(
			RIGHT_MOVE_KEY[i],
			LEFT_MOVE_KEY[i],
			JUMP_MOVE_KEY[i],
			TACKLE_MOVE_KEY[i]);
	}

	//�I�u�W�F�N�g������
	for (auto& objs : objs_) { objs->Init(); }

	//���ԏ�����
	time_->Init();

	//�J�E���g�_�E���̐ݒ�
	strCnt_ = COUNTDOWN;

	//�������
	ChangeState(STATE::START);
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
<<<<<<< HEAD
	// �X�V�X�e�b�v
	stateGameUpdate_();
=======

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
>>>>>>> 2e3f2a964f8ab0512986127c62e45d1b4ceef81b

	//�V�[���J��
	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		SceneManager::GetInstance().
			ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameScene::ChangeState(STATE state)
{
	// ��ԕύX
	state_ = state;

	// �e��ԑJ�ڂ̏�������
	stateChanges_[state_]();
}

void GameScene::ChangeStart(void)
{
	stateGameUpdate_ = std::bind(&GameScene::StartUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::StartDraw, this);
}

void GameScene::ChangePlay(void)
{
	stateGameUpdate_ = std::bind(&GameScene::PlayUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::PlayDraw, this);
}

void GameScene::ChangeRezalt(void)
{
	stateGameUpdate_ = std::bind(&GameScene::RezaltUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::RezaltDraw, this);
}

void GameScene::StartUpdate(void)
{
	//�J�E���g�_�E��
	strCnt_ -= SceneManager::GetInstance().GetDeltaTime();

	//���ԂɂȂ�����
	if (strCnt_ <= 0.0f)
	{
		ChangeState(STATE::PLAY);
	}
}

void GameScene::PlayUpdate(void)
{
	//���Ԍo�ߏ���
	time_->Update();

	//�X�N���[���֌W�̏���
	ScrollManager::GetInstance().Update();

	//�v���C���[�̍X�V
	for (auto& player : players_) { player->Update(); }

	//�I�u�W�F�N�g�̍X�V
	for (auto& objs : objs_) { objs->Update(); }

	//�Փ˔���
	Collision();

	//�Q�[���I������
	CheckGameOver();
}

void GameScene::RezaltUpdate(void)
{
	//�v���C���[�̍X�V(�A�j���[�V�����Đ��̂���)
	for (auto& player : players_) { player->Update(); }

	//�V�[���J��
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
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
<<<<<<< HEAD
	DrawBox(
	0, 0,
	Application::SCREEN_SIZE_X,
	Application::SCREEN_SIZE_Y,
	0x00ffff,
	true);

	//�e��I�u�W�F�N�g�`�揈��
	//���X�e�[�W�͐�΃v���C���[���O�̕`��
	players_[sceneManager_.GetScreenCount()]->Draw();
	objs_[sceneManager_.GetScreenCount()]->Draw();

	//�e��Ԃ��Ƃ̕`��
	stateGameDraw_();

=======
>>>>>>> 2e3f2a964f8ab0512986127c62e45d1b4ceef81b
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

void GameScene::Collision()
{
	//�v���C���[�ƃI�u�W�F�N�g���m�̏Փˏ���
	for (int i = 0; i < playNum_; i++) {
		auto& objs = objs_[i]->GetObjects();
		for (auto& obj : objs)
		{
			//�I�u�W�F�N�g��NONE�̏ꍇ�������������։�
			if (obj->GetState() == ObjectBase::STATE::NONE) { continue; }

			//�Փ˔���
			if (Utility::IsHitSpheres(
				players_[i]->GetTransform().pos,
				players_[i]->GetRadius(),
				obj->GetTransform().pos,
				obj->GetRadius()))
			{
				//�Փ˔����̏���
				obj->OnCollision(*players_[i]);
			}
		}
	}
}

void GameScene::StartDraw()
{
	DrawFormatString(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y,
		0xff0000,
		"%d",
		(int)strCnt_);
}

void GameScene::PlayDraw()
{
	//���Ԃ�X�R�A����UI��`��\��
	time_->Draw();
}

void GameScene::RezaltDraw()
{
	int score = ScoreBank::GetInstance().GetScore();

	DrawFormatString(
		Application::SCREEN_HALF_X - 64,
		Application::SCREEN_HALF_Y,
		0x000000,
		"GameOver");

	DrawFormatString(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y + 20,
		0x000000,
		"score = %d",
		score);
}

void GameScene::DebagDraw()
{
<<<<<<< HEAD
	for (int i = 0; i < playNum_; i++) {
		players_[i]->DebagDraw();
	}
=======
	////�f�o�b�O�n�̕`��͂����ɏ���
	DrawBox(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0xfff000,
		true);
>>>>>>> 2e3f2a964f8ab0512986127c62e45d1b4ceef81b
}

void GameScene::CheckGameOver()
{
	//�v���C���[�����S�����ꍇ
	for (int i = 0; i < playNum_; i++) {
		if (players_[i]->GetState() == Player::STATE::DEATH){
			//���U���g�Ɉڂ�
			ChangeState(STATE::REZALT);
		}
	}
}