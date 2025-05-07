#include "../Manager/ResourceManager.h"
#include "../Utility/Utility.h"
#include "../Common/Quaternion.h"
#include "TitleMesh.h"

TitleMesh::TitleMesh()
{
	int i = -1;
	for (int i = 0; i < ALPHABET_IMG_NUM; i++) { imgAlphabet_[i] = &i; }
	cnt_ = -1;
	deg_ = 0.0f;
	ex_ = 0.0f;
	exSpeed_ = 0.0f;
	for (int i = 0; i < MESH_FONT_NUM; i++) { fonts_[i] = {}; }
}

void TitleMesh::Load()
{
	imgAlphabet_[0] = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_UI).handleIds_;
}

void TitleMesh::Init()
{
	cnt_ = 0;
	deg_ = DEG;// �p�x
	ex_ = 1.0f;
	exSpeed_ = EX_SPEED;


	VECTOR norm = VGet(0.0f, 0.0f, -1.0f);	//�@���x�N�g���̏������p
	MeshText m;								//���b�V���t�H���g�̉��̈�
	VECTOR fPos =FIRST_POS;					//�ꕶ���ڂ̏������W

	for (int i = 0; i < MESH_FONT_NUM; i++)
	{
		//�摜�������
		Vector2 num = { i , 0 };

		//�`�撆���ʒu
		m.center_ = VAdd(fPos, { i * TEXT_INTERVEL , 0 , 0 });

		//����
		m.vertices_[0].pos = VAdd(m.center_, { FONT_SIZE_H, FONT_SIZE_H, 0.0f });
		m.vertices_[0].norm = norm;
		m.vertices_[0].dif = GetColorU8(COLOR_LT.r, COLOR_LT.g, COLOR_LT.b, COLOR_LT.a);
		m.vertices_[0].u = 1.0f / TITLE_UI_NUM_X * num.x;
		m.vertices_[0].v = 1.0f / TITLE_UI_NUM_Y * num.y;

		//�E��
		m.vertices_[1].pos = VAdd(m.center_, { -FONT_SIZE_H, FONT_SIZE_H, 0.0f });
		m.vertices_[1].norm = norm;
		m.vertices_[1].dif = GetColorU8(COLOR_RT.r, COLOR_RT.g, COLOR_RT.b, COLOR_RT.a);
		m.vertices_[1].u = 1.0f / TITLE_UI_NUM_X * (num.x + 1);
		m.vertices_[1].v = 1.0f / TITLE_UI_NUM_Y * num.y;

		//����
		m.vertices_[2].pos = VAdd(m.center_, { FONT_SIZE_H, -FONT_SIZE_H, 0.0f });
		m.vertices_[2].norm = norm;
		m.vertices_[2].dif = GetColorU8(COLOR_LB.r, COLOR_LB.g, COLOR_LB.b, COLOR_LB.a);
		m.vertices_[2].u = 1.0f / TITLE_UI_NUM_X * num.x;
		m.vertices_[2].v = 1.0f / TITLE_UI_NUM_Y * (num.y + 1);

		//�E��
		m.vertices_[3].pos = VAdd(m.center_, { -FONT_SIZE_H, -FONT_SIZE_H, 0.0f });
		m.vertices_[3].norm = norm;
		m.vertices_[3].dif = GetColorU8(COLOR_RB.r, COLOR_RB.g, COLOR_RB.b, COLOR_RB.a);
		m.vertices_[3].u = 1.0f / TITLE_UI_NUM_X * (num.x + 1);
		m.vertices_[3].v = 1.0f / TITLE_UI_NUM_Y * (num.y + 1);

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

void TitleMesh::Update()
{
	//��]�������߂�
	Quaternion qua = Quaternion::AngleAxis(Utility::Deg2RadF(deg_), Utility::AXIS_Y);

	//�J�E���g�X�V
	cnt_++;

	for (int j = 0; j < MESH_FONT_NUM; j++)
	{
		//�������s�������f
		if (cnt_ <= j * MESH_UPD_INTERVAL ||			//�J�E���g�����ʖ������ĂȂ��Ƃ�
			fonts_[j].state_ == ROT_STATE::NONE)		//��]���I�������
		{
			continue;	//�������s��Ȃ�
		}

		//z���ړ���
		float move = MESH_MOVE_Z;

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
			if (fonts_[j].rots_ >= ROT_STATE_START)
			{
				fonts_[j].state_ = ROT_STATE::HALF;
			}
			break;

		case ROT_STATE::HALF:
			if (fonts_[j].rots_ >= ROT_STATE_HALF)
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

void TitleMesh::Draw()
{
	//���b�V���e�L�X�g
	for (int j = 0; j < MESH_FONT_NUM; j++)
	{
		VERTEX3D vertices1[VERTICES] = { fonts_[j].vertices_[0],fonts_[j].vertices_[1], fonts_[j].vertices_[2] };
		VERTEX3D vertices2[VERTICES] = { fonts_[j].vertices_[1],fonts_[j].vertices_[3], fonts_[j].vertices_[2] };

		DrawPolygon3D(vertices1, 1, *imgAlphabet_[0], true); // �O�p�`1
		DrawPolygon3D(vertices2, 1, *imgAlphabet_[0], true); // �O�p�`2
	}
}
