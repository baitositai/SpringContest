#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "../Application.h"
#include "Resource.h"

// �I�����c����摜
constexpr int ALPHABET_NUM_X = 10;
constexpr int ALPHABET_NUM_Y = 6;
constexpr int ALPHABET_IMG_SIZE_X = 320;
constexpr int ALPHABET_IMG_SIZE_Y = 192;
constexpr int ALPHABET_SIZE_X = ALPHABET_IMG_SIZE_X / ALPHABET_NUM_X;
constexpr int ALPHABET_SIZE_Y = ALPHABET_IMG_SIZE_Y / ALPHABET_IMG_SIZE_Y;



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

		//���f��
		PLAYER,
		SKY_DOME,
		ENEMY,
		STAGE,
		STAGERIGHT,
		STAGELEFT
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

