#pragma once
#include "SceneBase.h"
#include "../framework.h"
#include "../Common/Vector2.h"
#include "../Manager/ResourceManager.h"

class TitleScene : public SceneBase
{

public:

	enum class ROT_STATE
	{
		NONE,
		START,	//�J�n
		HALF,	//����]�ς�
	};

	//�^�C�g���t�H���g�T�C�Y
	static constexpr int MES_FONT_SIZE = 28;

	//���_��
	static constexpr int VERTEXS = 4;

	//�t�H���g�T�C�Y
	static constexpr float FONT_SIZE = 50;
	static constexpr float FONT_SIZE_H = FONT_SIZE / 2;

	//�e�L�X�g�̊Ԋu
	static constexpr float TEXT_INTERVEL = 40;

	//���b�V�p�t�H���g��
	static constexpr int  MESH_FONT_NUM =12;

	//�A���t�@�x�b�g
	static constexpr int ALPHABET_IMG_NUM = ALPHABET_NUM_X * ALPHABET_SIZE_Y;

	// �R���X�g���N�^
	TitleScene(SceneManager& manager);

	// �f�X�g���N�^
	~TitleScene(void) = default;

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& ins) override;
	void Draw(void) override;
	void Release(void) override;

private:	
	// �e�L�X�g�摜
	int* imgTexts_[ALPHABET_IMG_NUM];

	// ���b�Z�[�W�t�H���g
	int mesFont_;

	//��]�J�n�J�E���g
	int cnt_;

	//��]�p�p�x
	float deg_;

	//�g��k����
	float ex_;

	//�g��k���X�s�[�h
	float exSpeed_;

	//���΍��W
	//VECTOR rPos_[VERTEXS];

	// ���b�V���p���
	struct MeshText
	{
		float rots_;					//��]��

		ROT_STATE state_;				//��]���

		Vector2 fontNumber_;			//�摜�̃t�H���g�Ǘ��ԍ�

		VECTOR center_;					//���b�V�������ʒu

		VECTOR relative_[VERTEXS];		//���΍��W

		VERTEX3D vertices_[VERTEXS];	//���b�V�����_���
	};

	// ���b�V���̃t�H���g���
	MeshText fonts_[MESH_FONT_NUM];

	// �X�V�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	// �`��֐�
	void LoadingDraw(void);
	void NormalDraw(void);

	// ���b�V��������
	void MeshInit();

	// ���b�V���X�V
	void MeshUpdate();

};