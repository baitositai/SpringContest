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
	updateFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&SelectScene::LoadingDraw, this);

	//������
	image_ = -1;
	imgSelect_ = -1;
	imgSpeech_ = -1;
	step_ = -1.0f;
}

void SelectScene::Load()
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂����s����
	SetUseASyncLoadFlag(true);

	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);	

	//�摜�̓ǂݍ���
	image_=LoadGraph( "Data/Image/select.png");
	imgSelect_ =LoadGraph( "Data/Image/TackleSelect.png");
	imgSpeech_ =LoadGraph( "Data/Image/Speech.png");

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

void SelectScene::Init()
{
	step_ = 0.0f; // �X�e�b�v��������

	//�����Đ�
	SoundManager::GetInstance().AdjustVolume(SoundManager::SOUND::SELECT_BGM, VOLUME);
	SoundManager::GetInstance().Play(SoundManager::SOUND::SELECT_BGM);
}

void SelectScene::Update(InputManager& input)
{
	updateFunc_(input);
	return;
}

void SelectScene::Draw()
{
	drawFunc_();
	return;
}

void SelectScene::CommonDraw()
{
}

void SelectScene::Release()
{
	//�t�H���g�폜
	DeleteFontToHandle(loadFont_);

	//�摜�̉��
	DeleteGraph(imgSpeech_);
	DeleteGraph(imgSelect_);
	DeleteGraph(image_);

	//���y���~
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SELECT_BGM);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::CHANGE_SCENE_SE);
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
		updateFunc_ = [&](InputManager& input) {NormalUpdate(input); };

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

	step_ += PERIOD; // �X�e�b�v��i�߂�
}

void SelectScene::LoadingDraw()
{
	DrawNowLoading();
}

void SelectScene::NormalDraw()
{
	//��ʂ̕`��
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, image_, TRUE);

	// �h��ɂ��Y���W�̃I�t�Z�b�g���v�Z�isin�g���g���j
	float offsetY = sinf(step_) * AMPLITUDE;

	// �摜�̕`��ʒu
	int drawX = SPEECH_POS_X; // �C�ӂ�X�ʒu
	int drawY = SPEECH_POS_Y + (int)offsetY; // �h���������Y�ʒu

	//�X�s�[�`�o�u���̕`��
	DrawRotaGraph(
		drawX,
		drawY,
		1.0f,
		0.0f,
		imgSpeech_,
		true,
		false);

	// �ȉ~��`��
	//���S�ʒu�����߂�
	Vector2 cPos = { 0, 0 };
	int cr = 0;
	if (DataBank::GetInstance().Output().autoTackle_)
	{
		cPos = { ON_POS_X, ON_POS_Y }; cr = 0xff0000; 
	}
	else 
	{
		cPos = { OFF_POS_X, OFF_POS_Y }; cr = 0x0000ff;
	}
	DrawRotaGraph(
		cPos.x,
		cPos.y,
		1.0f,
		0.0f,
		imgSelect_,
		true,
		false);
}

void SelectScene::CheckPlayerTackle()
{
	auto & data = DataBank::GetInstance();
	//�I���̎��̓I�t
	if (data.Output().autoTackle_) 
	{ 
		data.Input(false);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SWITCH_OFF_SE);
	}
	//�I�t�̎��̓I��
	else 
	{ 
		data.Input(true);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SWITCH_ON_SE);
	}
}
