#pragma once
#include "../../framework.h"	//������DXLib���̗l�X�ȃ��C�u�������܂Ƃ߂Ă�(�v���W�F�N�g���傫���Q�[���̏ꍇ���̂����͂����߂��Ȃ���)

class StageBase;

class StageManager
{
public:

	//�R���X�g���N�^
	StageManager();

	//�f�X�g���N�^(���ɏ������Ƃ��Ȃ�����default�����Ƃ�)
	~StageManager() = default;

	void Load();	//���f����摜,���y���̓ǂݍ���
	void Init();	//�ϐ����̏�����
	void Update();	//�X�V����
	void Draw();	//�`�揈��
	void Release();	//�������

private:

	//�X�e�[�W�̓��I�z��
	std::vector<StageBase*> stages_;

	//�X�e�[�W�̏o���J�E���g
	int stageSpawnCounter_;

	//�X�e�[�W�̐�
	int stageSpawn_;
};

