#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/DataBank.h"
#include "../Manager/ScrollManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/Effect2DManager.h"
#include "../Manager/Effect2DManagerContainer.h"
#include "../Utility/Utility.h"
#include "../Object/Character/Player.h"
#include "../Object/ScrollObject/ObjectManager.h"
#include "../Object/TimeCount.h"
#include "../Object/Stage/Stage.h"
#include "../Object/Stage/SkyDome.h"
#include "../Object/UI/PlayerUI.h"
#include "../Object/CountDown.h"
#include "../Object/Hinder/HinderManager.h"
#include "../Object/GameBGM.h"

GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updateFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);

	players_.clear();
	objs_.clear();	
	stage_ = nullptr;
	uis_ = nullptr;
	bgm_ = nullptr;
	sky_ = nullptr;
	hinder_ = nullptr;
	state_ = STATE::NONE;
	strCnt_ = -1.0f;
	playNum_ = -1;

	stateChanges_.emplace(STATE::START, std::bind(&GameScene::ChangeStart, this));
	stateChanges_.emplace(STATE::PLAY, std::bind(&GameScene::ChangePlay, this));
	stateChanges_.emplace(STATE::RESULT, std::bind(&GameScene::ChangeResult, this));
}

void GameScene::Load()
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂��s��
	SetUseASyncLoadFlag(true);	
	
	//�G�t�F�N�g�֌W���������ŏ��ɍs��
	Effect2DManagerContainer::GetInstance().Init();

	//�l���ݒ�
	playNum_ = 1;
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { playNum_ = SceneManager::PLAYER_MAX; }
	DataBank::GetInstance().InputPlayNum(playNum_);

	//�v���C���[
	for (int i = 0; i < playNum_; i++) 
	{
		auto player = std::make_shared<Player>();
		DataBank::GetInstance().Input(i);
		player->Load();
		players_.emplace_back(std::move(player));
	}

	//�I�u�W�F�N�g
	for (int i = 0; i < playNum_; i++) 
	{
		auto objs = std::make_unique<ObjectManager>();
		objs->Load();
		objs_.emplace_back(std::move(objs));
	}

	//����
	time_ = std::make_unique<TimeCount>();
	time_->Load();

	//�X�e�[�W
	stage_ = std::make_unique<Stage>();
	stage_->Load();

	//UI
	uis_ = std::make_unique<PlayerUI>();
	uis_->Load();

	//�J�E���g�_�E��
	cntDown_ = std::make_unique<CountDown>();
	cntDown_->Load();

	//BGM
	bgm_ = std::make_unique<GameBGM>();
	bgm_->Load();

	//�X�J�C�h�[��
	sky_ = std::make_unique<SkyDome>();
	sky_->Load();

	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		//�W�Q�֌W
		hinder_ = std::make_unique<HinderManager>();
		hinder_->Load();
	}

	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

	//�T�E���h�֌W
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::CHANGE_SCENE_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::CHANGE_SCENE_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::CLEAR_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::CLEAR_SE).handleId_);

	//�J�����̐ݒ�
	auto cameras = SceneManager::GetInstance().GetCameras();
	for (int i = 0; i < cameras.size(); i++)
	{
		cameras[i]->ChangeMode(Camera::MODE::FIXED_POINT);
		cameras[i]->SetTargetPos(LOCAL_CAMERA_POS);
	}
}

void GameScene::Init()
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

	//�X�e�[�W�̏�����
	stage_->Init();

	//UI�̏�����
	uis_->Init();

	//�J�E���g�_�E��������
	cntDown_->Init();

	//BGM
	bgm_->Init();

	//�X�J�C�h�[��
	sky_->Init();

	//�W�Q�֌W������	
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		hinder_->Init();
	}

	//�������
	ChangeState(STATE::START);

	//�X�s�[�h�֌W�̏�����
	ScrollManager::GetInstance().Init();

	//�X�R�A������
	ScoreBank::GetInstance().Init();
}

void GameScene::Update(InputManager& input)
{
	updateFunc_(input);
	return;
}

void GameScene::Draw()
{
	drawFunc_();
	return;
}

void GameScene::Release()
{
	//�e�C���X�^���X�̃����[�X����
	time_->Release();
	cntDown_->Release();
	bgm_->Release();
	for (auto& obj : objs_) { obj->Release(); }
	for (auto& player : players_) { player->Release(); }

	//�t�H���g�폜
	DeleteFontToHandle(loadFont_);
}

void GameScene::CommonDraw()
{	
	if (state_ == STATE::NONE) { return; }
	//�e��Ԃ��Ƃ̕`��
	stateGameDraw_();
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
		updateFunc_ = [&](InputManager& input) {NormalUpdate(input); };
		
		//�`��֐��̃Z�b�g
		drawFunc_ = std::bind(&GameScene::NormalDraw, this);
	}
}

void GameScene::NormalUpdate(InputManager& ins)
{
	// �X�V�X�e�b�v
	stateGameUpdate_();

	//�X�J�C�h�[���X�V
	sky_->Update();

	//2D�G�t�F�N�g�X�V
	Effect2DManagerContainer::GetInstance().Update();
}

void GameScene::ChangeState(STATE state)
{
	// ��ԕύX
	state_ = state;

	// �e��ԑJ�ڂ̏�������
	stateChanges_[state_]();
}

void GameScene::ChangeStart()
{
	stateGameUpdate_ = std::bind(&GameScene::StartUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::StartDraw, this);
}

void GameScene::ChangePlay()
{
	stateGameUpdate_ = std::bind(&GameScene::PlayUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::PlayDraw, this);
}

void GameScene::ChangeResult()
{
	stateGameUpdate_ = std::bind(&GameScene::ResultUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::ResultDraw, this);

	//������Ԃ̊m�F
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { CheckWinPlayer(); }

	//BGM��~
	bgm_->Stop();

	//�N���ASE
	SoundManager::GetInstance().Play(SoundManager::SOUND::CLEAR_SE);
}

void GameScene::StartUpdate()
{
	//�J�E���g�_�E��
	cntDown_->Update();

	//���ԂɂȂ�����
	if (cntDown_->IsStart())
	{
		ChangeState(STATE::PLAY);
	}
}

void GameScene::PlayUpdate()
{
	//���Ԍo�ߏ���
	time_->Update();

	//�v���C���[�̍X�V
	for (int i = 0; i < players_.size(); i++)
	{
		DataBank::GetInstance().Input(i);
		players_[i]->Update();
	}

	//�I�u�W�F�N�g�̍X�V
	for (int i = 0; i < objs_.size(); i++)
	{
		DataBank::GetInstance().Input(i);
		objs_[i]->Update();
	}

	//�W�Q�֌W�̍X�V
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		hinder_->Update();
	}

	//�X�e�[�W�̍X�V
	stage_->Update();

	//UI�̍X�V
	uis_->Update();

	//�Փ˔���
	Collision();

	//�Q�[���I�[�o�[����
	CheckGameOver();
}

void GameScene::ResultUpdate()
{
	//�v���C���[�̍X�V(�A�j���[�V�����Đ��̂���)
	for (auto& player : players_) { player->Update(); }

	//�V�[���J��
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);

		//�V�[���J��SE
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);

		//SE�̒�~
		SoundManager::GetInstance().Stop(SoundManager::SOUND::CLEAR_SE);
	}
}

void GameScene::LoadingDraw()
{
	//�unow loading�v�̕`��
	DrawNowLoading();
}

void GameScene::NormalDraw()
{
	int playerId = sceneManager_.GetScreenCount();

	//�X�J�C�h�[��
	sky_->Draw();

	//�X�e�[�W
	stage_->Draw();

	//�v���C���[
	players_[playerId]->Draw();

	//�I�u�W�F�N�g�֘A
	objs_[sceneManager_.GetScreenCount()]->Draw();

	//�W�Q�֌W�̕`��
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		hinder_->Draw();
	}

	//�^�C��
	time_->Draw();

	//UI
	uis_->Draw(*players_[playerId]);
}

void GameScene::Collision()
{
	//�v���C���[�ƃI�u�W�F�N�g���m�̏Փˏ���
	for (int i = 0; i < playNum_; i++)
	{
		//�v���C���[ID��ݒ�
		DataBank::GetInstance().Input(i);

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
	cntDown_->Draw();
}

void GameScene::ResultDraw()
{
	//�N���A�`��
	uis_->ResultDraw();
}

void GameScene::PlayDraw()
{
	//���Ԃ�X�R�A����UI��`��\��
	time_->CommonDraw();
}

void GameScene::DebagDraw()
{
	for (int i = 0; i < playNum_; i++)
	{
		players_[i]->DebagDraw();
	}
}

void GameScene::CheckGameOver()
{
	//�v���C���[�����S�����ꍇ
	for (int i = 0; i < playNum_; i++) 
	{
		if (players_[i]->GetState() == Player::STATE::DEATH){

			//���U���g�Ɉڂ�
			ChangeState(STATE::RESULT);
		}
	}			
}

void GameScene::CheckWinPlayer()
{
	//������Ԃ̃v���C���[�̏�Ԃ�ύX
	for (int j = 0; j < playNum_; j++)
	{
		if (players_[j]->GetState() != Player::STATE::DEATH) { players_[j]->ChangeState(Player::STATE::WIN); }
	}

	//�Q�[���̏�����Ԃ𒲂ׂ�
	if (players_[0]->GetState() == Player::STATE::WIN &&
		players_[1]->GetState() == Player::STATE::WIN)
	{
		//��������
		uis_->ChangeWinState(PlayerUI::WIN_STATE::DRAW);
	}
	else if (players_[0]->GetState() == Player::STATE::WIN)
	{
		//�v���C���[1�̏���
		uis_->ChangeWinState(PlayerUI::WIN_STATE::P1_WIN);
	}
	else if (players_[1]->GetState() == Player::STATE::WIN)
	{
		//�v���C���[2�̏���
		uis_->ChangeWinState(PlayerUI::WIN_STATE::P2_WIN);
	}
}
