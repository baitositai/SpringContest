#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "Resource.h"

// �I�����c����摜
constexpr int ALPHABET_NUM_X = 10;
constexpr int ALPHABET_NUM_Y = 6;
constexpr int ALPHABET_IMG_SIZE_X = 320;
constexpr int ALPHABET_IMG_SIZE_Y = 192;
constexpr int ALPHABET_SIZE_X = ALPHABET_IMG_SIZE_X / ALPHABET_NUM_X;
constexpr int ALPHABET_SIZE_Y = ALPHABET_IMG_SIZE_Y / ALPHABET_NUM_Y;

//�v���C���[�A�C�R��
constexpr int PLAYER_ICONS_NUM_X = 1;
constexpr int PLAYER_ICONS_NUM_Y = 2;
constexpr int PLAYER_ICONS_IMG_SIZE_X = 128;
constexpr int PLAYER_ICONS_IMG_SIZE_Y = 256;
constexpr int PLAYER_ICONS_SIZE = 128;

//�����摜
constexpr int NUMBERS_NUM_X = 5;
constexpr int NUMBERS_NUM_Y = 2;
constexpr int NUMBERS_IMG_SIZE_X = 640;
constexpr int NUMBERS_IMG_SIZE_Y = 256;
constexpr int NUMBERS_SIZE = 128;

//����2�摜
constexpr int NUMBERS2_NUM_X = 5;
constexpr int NUMBERS2_NUM_Y = 2;
constexpr int NUMBERS2_IMG_SIZE_X = 210;
constexpr int NUMBERS2_IMG_SIZE_Y = 84;
constexpr int NUMBERS2_SIZE = 42;

//�v���C���[UI
constexpr int PLAYER_UI_NUM_X = 1;
constexpr int PLAYER_UI_NUM_Y = 2;
constexpr int PLAYER_UI_IMG_SIZE_X = 384;
constexpr int PLAYER_UI_IMG_SIZE_Y = 192;
constexpr int PLAYER_UI_SIZE_X = PLAYER_UI_IMG_SIZE_X / PLAYER_UI_NUM_X;
constexpr int PLAYER_UI_SIZE_Y = PLAYER_UI_IMG_SIZE_Y / PLAYER_UI_NUM_Y;

class ResourceManager :
	public StaticSingleton<ResourceManager>
{

public:

	// ���\�[�X��
	enum class SRC
	{
		//�摜
		ALPHABET,
		PLAYER_SHADOW,
		NUMBER,
		NUMBER2,
		PLAYER_UI,
		TIMER_UI,
		WIN_UI,
		TITLE_LOGO,
		DRAW,

		//UI�摜
		POWER_UI,
		LIFE_UI,
		SCORE_UI,
		HINDER,
		HINDER_GAGE,
		PLAYER_ICONS,
		LIFE,
		POWER,
		TITLE,
		TITLE_UI,
		TITLE_BACKGROUND,

		//���f��
		PLAYER,
		STAGE,
		SKY_DOME,
		ENEMY,
		BOMB,
		HEART,
		POTION,

		//�G�t�F�N�g
		TACKLE_EFK,
		STAR_DUST_EFK,

		//���y
		TITLE_BGM,
		SELECT_BGM,
		GAMEBGM1,
		GAMEBGM2,
		CHANGE_SCENE_SE,
		SWITCH_ON_SE,
		SWITCH_OFF_SE,
		TACKLE_SE,
		ITEM_GET_SE,
		DAMAGE_SE,
		COUNT_DOWN_SE,
		COUNT_3,
		COUNT_2,
		COUNT_1,
		COUNT_0,
		GO_SE,
		CLEAR_SE,
		JUMP_SE,
		BLAST_SE,
		ENEMY_DAMAGE_SE
	};

	// ������
	void Init(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	// ���\�[�X�̊��S�j��
	void Destroy(void);

	// ���\�[�X�̃��[�h
	Resource& Load(SRC src);

	// ���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	//�V���O���g���̐���
	THIS_CLASS_IS_STATIC_SINGLETON(ResourceManager);

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, std::unique_ptr<Resource>> resourcesMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource&> loadedMap_;	
	
	Resource dummy_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);

	// �f�X�g���N�^�����l
	~ResourceManager(void) = default;

	// �������[�h
	Resource& _Load(SRC src);

};

