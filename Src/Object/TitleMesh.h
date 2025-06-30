#pragma once
#include <DxLib.h>
#include "../Common/Vector2.h"

class TitleMesh
{

public:	
	
	//��]���
	enum class ROT_STATE
	{
		NONE,
		START,	//�J�n
		HALF,	//����]�ς�
	};

	//��]�p�p�x
	static constexpr float DEG = 2.0f;

	//�g��k���X�s�[�h
	static constexpr float EX_SPEED = 0.2f;

	//���_��
	static constexpr int VERTEXS = 4;

	//�e�L�X�g�̊Ԋu
	static constexpr float TEXT_INTERVEL = 40;

	//�t�H���g�T�C�Y
	static constexpr float FONT_SIZE = 50;
	static constexpr float FONT_SIZE_H = FONT_SIZE / 2;

	//���b�V�p�t�H���g��
	static constexpr int  MESH_FONT_NUM = 9;

	//�A���t�@�x�b�g
	static constexpr int ALPHABET_IMG_NUM = 9;

	//���_��
	static constexpr int VERTICES = 3;

	//���b�V���̉�]�����̃C���^�[�o�[��
	static constexpr int MESH_UPD_INTERVAL = 20;

	//���b�V����Z���̈ړ���
	static constexpr float MESH_MOVE_Z = -1.5f;

	//��]
	static constexpr float ROT_STATE_START = 90.0f;
	static constexpr float ROT_STATE_HALF = 180.0f;	
	
	//1�����ڂ̏������W
	static constexpr VECTOR FIRST_POS = { 370,400,-100 };

	//�F
	static constexpr COLOR_U8 COLOR_LT = { 255, 255, 255, 255 };//����
	static constexpr COLOR_U8 COLOR_RT = { 255, 0, 255, 255 };	//�E��
	static constexpr COLOR_U8 COLOR_LB = { 255, 255, 0, 255 };	//����
	static constexpr COLOR_U8 COLOR_RB = { 255, 255, 0, 255 };	//�E��

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TitleMesh();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitleMesh() = default;

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	void Load();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	//�A���t�@�x�b�g�摜
	int* imgAlphabet_[ALPHABET_IMG_NUM];

	//��]�J�n�J�E���g
	int cnt_;

	//��]�p�p�x
	float deg_;

	//�g��k����
	float ex_;

	//�g��k���X�s�[�h
	float exSpeed_;

	// ���b�V���p���
	struct MeshText
	{
		//��]��
		float rots_ = -1.0f;

		//��]���
		ROT_STATE state_ = ROT_STATE::NONE;

		//�摜�̃t�H���g�Ǘ��ԍ�
		Vector2 fontNumber_ = { -1,-1 };

		//���b�V�������ʒu
		VECTOR center_ = { -1,-1,-1 };

		//���΍��W
		VECTOR relative_[VERTEXS] =
		{ { -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 } };

		//���b�V�����_���
		VERTEX3D vertices_[VERTEXS] =
		{ { -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 } };
	};

	// ���b�V���̃t�H���g���
	MeshText fonts_[MESH_FONT_NUM];

};

