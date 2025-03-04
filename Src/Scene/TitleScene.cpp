#include "../Application.h"
#include "../Utility/Utility.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager& manager) :SceneBase(manager)
{
	//�e�평��������
	cnt_ = -1;
	deg_ = -1.0f;
	ex_ = -1.0f;
	exSpeed_ = -1.0f;
	mesFont_ = -1;

	int i = -1;
	for (auto& img : imgTexts_) { img = &i; }

	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&TitleScene::LoadingDraw, this);
}

void TitleScene::Load(void)
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂�true�ɂ���
	SetUseASyncLoadFlag(true);

	// �^�C�g�����S
	imgTexts_[0] = ResourceManager::GetInstance().Load(ResourceManager::SRC::ALPHABET).handleIds_;
	
	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::DOT).c_str(),
		LOAD_FONT_SIZE,
		0);
	mesFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::BOKUTACHI).c_str(),
		MES_FONT_SIZE,
		0);
}

void TitleScene::Init(void)
{
	//���b�V���̐ݒ�
	MeshInit();

	//�ϐ�������
	cnt_ = 0;
	deg_ = 2.0f;// �p�x
	ex_ = 1.0f;
	exSpeed_ = 0.2f;
}

void TitleScene::Update(InputManager& input)
{
	updataFunc_(input);
	return;
}

void TitleScene::Draw(void)
{
	drawFunc_();
	return;
}

void TitleScene::Release(void)
{
	DeleteFontToHandle(loadFont_);
	DeleteFontToHandle(mesFont_);
}

void TitleScene::LoadingUpdate(InputManager& input)
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
		drawFunc_ = std::bind(&TitleScene::NormalDraw, this);
	}
}

void TitleScene::NormalUpdate(InputManager& ins)
{
	MeshUpdate();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT);
	}
}

void TitleScene::LoadingDraw(void)
{
	//�unow loading�v�̕`��
	DrawNowLoading();
}

void TitleScene::NormalDraw(void)
{
	//�w�i
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0xffb6c1, true);
	for (int j = 0; j < MESH_FONT_NUM; j++)
	{
		VERTEX3D vertices1[3] = { fonts_[j].vertices_[0],fonts_[j].vertices_[1], fonts_[j].vertices_[2] };
		VERTEX3D vertices2[3] = { fonts_[j].vertices_[1],fonts_[j].vertices_[3], fonts_[j].vertices_[2] };

		DrawPolygon3D(vertices1, 1, *imgTexts_[0], true); // �O�p�`1
		DrawPolygon3D(vertices2, 1, *imgTexts_[0], true); // �O�p�`2
	}

	SetDrawScreen(sceneManager_.GetMainScreen());

	int cx = Application::SCREEN_HALF_X;
	int cy = Application::SCREEN_HALF_Y;

	//�V�[���J��
	std::string mes = "�X�y�[�X�������Ă�";
	DrawFormatStringToHandle(
		cx - mes.length() * MES_FONT_SIZE / 2,
		cy + 150,
		0xffffff,
		mesFont_,
		mes.c_str());
}

void TitleScene::MeshInit()
{
#pragma region ���b�V���p�ϐ��̐錾

	VECTOR norm = VGet(0.0f, 0.0f, -1.0f);	//�@���x�N�g���̏������p
	MeshText m;								//���b�V���t�H���g�̉��̈�
	VECTOR fPos = { -180,100,0 };			//�ꕶ���ڂ̏������W

	for (int i = 0; i < MESH_FONT_NUM; i++)
	{
		switch (i)
		{
		case 0: //L
			m.fontNumber_ = { 1,1 };
			break;

		case 1: //e
			m.fontNumber_ = { 0,3 };
			break;

		case 2: //t
			m.fontNumber_ = { 5,4 };
			break;

		case 3: //s
			m.fontNumber_ = { 4,4 };
			break;

		case 4: //G
			m.fontNumber_ = { 6,0 };
			break;

		case 5: //a
			m.fontNumber_ = { 6,2 };
			break;

		case 6: //m
			m.fontNumber_ = { 8,3 };
			break;

		case 7: //e
			m.fontNumber_ = { 0,3 };
			break;

		case 8: //P
			m.fontNumber_ = { 5,1 };
			break;

		case 9: //l
			m.fontNumber_ = { 7,3 };
			break;

		case 10: //a
			m.fontNumber_ = { 6,2 };
			break;

		case 11: //y
			m.fontNumber_ = { 0,5 };
			break;

		}

		//�摜�������
		Vector2 num = m.fontNumber_;

		//�`�撆���ʒu
		m.center_ = VAdd(fPos, { i * TEXT_INTERVEL , 0 , 0 });

		//����
		m.vertices_[0].pos = VAdd(m.center_, { FONT_SIZE_H, FONT_SIZE_H, 0.0f });
		m.vertices_[0].norm = norm;
		m.vertices_[0].dif = GetColorU8(255, 255, 255, 255);
		m.vertices_[0].u = 1.0f / ALPHABET_NUM_X * num.x;
		m.vertices_[0].v = 1.0f / ALPHABET_NUM_Y * num.y;

		//�E��
		m.vertices_[1].pos = VAdd(m.center_, { -FONT_SIZE_H, FONT_SIZE_H, 0.0f });
		m.vertices_[1].norm = norm;
		m.vertices_[1].dif = GetColorU8(255, 0, 255, 255);
		m.vertices_[1].u = 1.0f / ALPHABET_NUM_X * (num.x + 1);
		m.vertices_[1].v = 1.0f / ALPHABET_NUM_Y * num.y;

		//����
		m.vertices_[2].pos = VAdd(m.center_, { FONT_SIZE_H, -FONT_SIZE_H, 0.0f });
		m.vertices_[2].norm = norm;
		m.vertices_[2].dif = GetColorU8(0, 255, 255, 255);
		m.vertices_[2].u = 1.0f / ALPHABET_NUM_X * num.x;
		m.vertices_[2].v = 1.0f / ALPHABET_NUM_Y * (num.y + 1);

		//�E��
		m.vertices_[3].pos = VAdd(m.center_, { -FONT_SIZE_H, -FONT_SIZE_H, 0.0f });
		m.vertices_[3].norm = norm;
		m.vertices_[3].dif = GetColorU8(0, 255, 255, 255);
		m.vertices_[3].u = 1.0f / ALPHABET_NUM_X * (num.x + 1);
		m.vertices_[3].v = 1.0f / ALPHABET_NUM_Y * (num.y + 1);
#pragma endregion

		//���΍��W
		for (int j = 0; j < VERTEXS; j++)
		{
			m.relative_[j] = VSub(m.vertices_[j].pos, m.center_);
		}

		m.state_ = ROT_STATE::START;
		m.rots_ = 0.0f;

		//���̊i�[
		fonts_[i] = m;
	}
}

void TitleScene::MeshUpdate()
{
	//��]�������߂�
	Quaternion qua = Quaternion::AngleAxis(Utility::Deg2RadF(deg_), Utility::AXIS_Y);

	//�J�E���g�X�V
	cnt_++;

	for (int j = 0; j < MESH_FONT_NUM; j++)
	{
		//�������s�������f
		if (cnt_ <= j * 20 ||							//�J�E���g�����ʖ������ĂȂ��Ƃ�
			fonts_[j].state_ == ROT_STATE::NONE)		//��]���I�������
		{
			continue;	//�������s��Ȃ�
		}

		//z���ړ���
		float move = -1.0f;

		//���S�ʒu�𓮂���
		if (fonts_[j].state_ == ROT_STATE::HALF) { move *= -1; }
		fonts_[j].center_.z += move;

		for (int i = 0; i < VERTEXS; i++)
		{
			//��]��̑��΍��W
			fonts_[j].relative_[i] = Quaternion::PosAxis(qua, fonts_[j].relative_[i]);

			//���W
			fonts_[j].vertices_[i].pos = VAdd(fonts_[j].center_, fonts_[j].relative_[i]);
		}

		//��]�ʂ̉��Z
		fonts_[j].rots_ += deg_;

		//�X�e�[�g���Ƃ̏���
		switch (fonts_[j].state_)
		{
		case ROT_STATE::START:
			if (fonts_[j].rots_ >= 90.0f)
			{
				fonts_[j].state_ = ROT_STATE::HALF;
			}
			break;

		case ROT_STATE::HALF:
			if (fonts_[j].rots_ >= 180.0f)
			{
				fonts_[j].rots_ = 0.0f;		//��]�ʏ�����
				fonts_[j].state_ = ROT_STATE::NONE;

				//���X�g�̏������I������
				if (j == MESH_FONT_NUM - 1)
				{
					cnt_ = 0;
					for (int i = 0; i < MESH_FONT_NUM; i++)
					{
						fonts_[i].state_ = ROT_STATE::START;
					}
				}
			}
			break;

		}
	}
}
