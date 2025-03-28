#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/DataBank.h"
#include "../Utility/Utility.h"
#include "SelectScene.h"

SelectScene::SelectScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&SelectScene::LoadingDraw, this);

	//������
	image_ = -1;
}

SelectScene::~SelectScene(void)
{
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SWITCH_OFF_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SWITCH_ON_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::CHANGE_SCENE_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SELECT_BGM);
}

void SelectScene::Load(void)
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

	//�摜�̓ǂݍ���
	image_=LoadGraph( "Data/Image/select.png");

	//�T�E���h�̃��[�h
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::BGM,
		SoundManager::SOUND::SELECT_BGM,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SELECT_BGM).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::CHANGE_SCENE_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::CHANGE_SCENE_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::SWITCH_ON_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SWITCH_ON_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::SWITCH_OFF_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SWITCH_OFF_SE).handleId_);
}

void SelectScene::Init(void)
{
	//�����Đ�
	SoundManager::GetInstance().Play(SoundManager::SOUND::SELECT_BGM);
}

void SelectScene::Update(InputManager& input)
{
	updataFunc_(input);
	return;
}

void SelectScene::Draw(void)
{
	drawFunc_();
	return;
}

void SelectScene::CommonDraw(void)
{
}

void SelectScene::Release(void)
{
	//�t�H���g�폜
	DeleteFontToHandle(loadFont_);

	//�摜�̉��
	DeleteGraph(image_);
}

void SelectScene::LoadingUpdate(InputManager& ins)
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
		drawFunc_ = std::bind(&SelectScene::NormalDraw, this);
	}
}

void SelectScene::NormalUpdate(InputManager& ins)
{
	//�V�[���J��
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{		
		DataBank::GetInstance().Input(SceneManager::MODE::MARASON);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);
		SoundManager::GetInstance().Stop(SoundManager::SOUND::SELECT_BGM);
	}
	else if (ins.IsTrgDown(KEY_INPUT_W))
	{
		DataBank::GetInstance().Input(SceneManager::MODE::VS);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);
		SoundManager::GetInstance().Stop(SoundManager::SOUND::SELECT_BGM);
	}

	//�v���C���[�̎����U���̗L��
	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		CheckPlayerTackle();
	}
}

void SelectScene::LoadingDraw(void)
{
	DrawNowLoading();
}

void SelectScene::NormalDraw(void)
{
	//��ʂ̕`��
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, image_, TRUE);
	// �ȉ~��`��
	//���S�ʒu�����߂�
	Vector2 cPos = { 0, 0 };
	int cr = 0;
	if (DataBank::GetInstance().Output().autoTackle_) { cPos = { 350, 550 }; cr = 0xff0000; }
	else { cPos = { 500, 550 }; cr = 0x0000ff;}
	DrawOval(cPos.x, cPos.y, 80, 60, cr, false);
}

void SelectScene::CheckPlayerTackle()
{
	auto & data = DataBank::GetInstance();
	//�I���̎��̓I�t
	if (data.Output().autoTackle_) { 
		data.Input(false);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SWITCH_OFF_SE);
	}
	//�I�t�̎��̓I��
	else { 
		data.Input(true);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SWITCH_ON_SE);
	}
}
