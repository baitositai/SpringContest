#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/ScrollManager.h"
#include "../Utility/Utility.h"
#include "../Object/Character/Player.h"
#include "../Object/ScrollObject/ObjectManager.h"
#include "../Object/TimeCount.h"

GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);

	player_ = nullptr;
	objs_ = nullptr;
	state_ = STATE::START;
	strCnt_ = 0.0f;

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

	//�v���C���[
	player_ = std::make_shared<Player>();
	player_->Load();

	//�I�u�W�F�N�g
	objs_ = std::make_unique<ObjectManager>();
	objs_->Load();

	//����
	time_ = std::make_unique<TimeCount>();
	time_->Load();

	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

	//�J����
	mainCamera->ChangeMode(Camera::MODE::FIXED_POINT);
	mainCamera->SetTargetPos(LOCAL_CAMERA_POS);
}

void GameScene::Init(void)
{
	//�v���C���[������
	player_->Init();

	//�I�u�W�F�N�g������
	objs_->Init();

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
	// �X�V�X�e�b�v
	stateGameUpdate_();

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
	player_->Update();

	//�I�u�W�F�N�g�̍X�V
	objs_->Update();

	//�Փ˔���
	Collision();

	//�Q�[���I������
	CheckGameOver();
}

void GameScene::RezaltUpdate(void)
{
	//�v���C���[�̍X�V(�A�j���[�V�����Đ��̂���)
	player_->Update();
}

void GameScene::LoadingDraw(void)
{
	//�unow loading�v�̕`��
	DrawNowLoading();
}

void GameScene::NormalDraw(void)
{
	DrawBox(
	0, 0,
	Application::SCREEN_SIZE_X,
	Application::SCREEN_SIZE_Y,
	0x00ffff,
	true);

	//�e��I�u�W�F�N�g�`�揈��
	//���X�e�[�W�͐�΃v���C���[���O�̕`��
	player_->Draw();
	objs_->Draw();

	//�e��Ԃ��Ƃ̕`��
	stateGameDraw_();

	//�f�o�b�O�`��
	DebagDraw();
}

void GameScene::Collision()
{
	//�v���C���[�ƃI�u�W�F�N�g���m�̏Փˏ���
	auto & objs = objs_->GetObjects();
	for (auto& obj : objs)
	{
		//�I�u�W�F�N�g��NONE�̏ꍇ�������������։�
		if (obj->GetState() == ObjectBase::STATE::NONE) { continue; }

		//�Փ˔���
		if (Utility::IsHitSpheres(
			player_->GetTransform().pos,
			player_->GetRadius(),
			obj->GetTransform().pos,
			obj->GetRadius()))
		{
			//�Փ˔����̏���
			obj->OnCollision(*player_);
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
	player_->DebagDraw();
}

void GameScene::CheckGameOver()
{
	//�v���C���[�����S�����ꍇ
	if (player_->GetState() == Player::STATE::DEATH)
	{
		//���U���g�Ɉڂ�
		ChangeState(STATE::REZALT);
	}
}