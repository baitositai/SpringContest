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
	deg_ = DEG;// 角度
	ex_ = 1.0f;
	exSpeed_ = EX_SPEED;


	VECTOR norm = VGet(0.0f, 0.0f, -1.0f);	//法線ベクトルの初期化用
	MeshText m;								//メッシュフォントの仮領域
	VECTOR fPos =FIRST_POS;					//一文字目の初期座標

	for (int i = 0; i < MESH_FONT_NUM; i++)
	{
		//画像分割情報
		Vector2 num = { i , 0 };

		//描画中央位置
		m.center_ = VAdd(fPos, { i * TEXT_INTERVEL , 0 , 0 });

		//左上
		m.vertices_[0].pos = VAdd(m.center_, { FONT_SIZE_H, FONT_SIZE_H, 0.0f });
		m.vertices_[0].norm = norm;
		m.vertices_[0].dif = GetColorU8(COLOR_LT.r, COLOR_LT.g, COLOR_LT.b, COLOR_LT.a);
		m.vertices_[0].u = 1.0f / TITLE_UI_NUM_X * num.x;
		m.vertices_[0].v = 1.0f / TITLE_UI_NUM_Y * num.y;

		//右上
		m.vertices_[1].pos = VAdd(m.center_, { -FONT_SIZE_H, FONT_SIZE_H, 0.0f });
		m.vertices_[1].norm = norm;
		m.vertices_[1].dif = GetColorU8(COLOR_RT.r, COLOR_RT.g, COLOR_RT.b, COLOR_RT.a);
		m.vertices_[1].u = 1.0f / TITLE_UI_NUM_X * (num.x + 1);
		m.vertices_[1].v = 1.0f / TITLE_UI_NUM_Y * num.y;

		//左下
		m.vertices_[2].pos = VAdd(m.center_, { FONT_SIZE_H, -FONT_SIZE_H, 0.0f });
		m.vertices_[2].norm = norm;
		m.vertices_[2].dif = GetColorU8(COLOR_LB.r, COLOR_LB.g, COLOR_LB.b, COLOR_LB.a);
		m.vertices_[2].u = 1.0f / TITLE_UI_NUM_X * num.x;
		m.vertices_[2].v = 1.0f / TITLE_UI_NUM_Y * (num.y + 1);

		//右下
		m.vertices_[3].pos = VAdd(m.center_, { -FONT_SIZE_H, -FONT_SIZE_H, 0.0f });
		m.vertices_[3].norm = norm;
		m.vertices_[3].dif = GetColorU8(COLOR_RB.r, COLOR_RB.g, COLOR_RB.b, COLOR_RB.a);
		m.vertices_[3].u = 1.0f / TITLE_UI_NUM_X * (num.x + 1);
		m.vertices_[3].v = 1.0f / TITLE_UI_NUM_Y * (num.y + 1);

		//相対座標
		for (int j = 0; j < VERTEXS; j++)
		{
			m.relative_[j] = VSub(m.vertices_[j].pos, m.center_);
		}

		m.state_ = ROT_STATE::START;
		m.rots_ = 0.0f;

		//情報の格納
		fonts_[i] = m;
	}
}

void TitleMesh::Update()
{
	//回転情報を求める
	Quaternion qua = Quaternion::AngleAxis(Utility::Deg2RadF(deg_), Utility::AXIS_Y);

	//カウント更新
	cnt_++;

	for (int j = 0; j < MESH_FONT_NUM; j++)
	{
		//処理を行うか判断
		if (cnt_ <= j * MESH_UPD_INTERVAL ||			//カウントが一定量満たしてないとき
			fonts_[j].state_ == ROT_STATE::NONE)		//回転し終わった時
		{
			continue;	//処理を行わない
		}

		//z軸移動量
		float move = MESH_MOVE_Z;

		//中心位置を動かす
		if (fonts_[j].state_ == ROT_STATE::HALF) { move *= -1; }
		fonts_[j].center_.z += move;

		for (int i = 0; i < VERTEXS; i++)
		{
			//回転後の相対座標
			fonts_[j].relative_[i] = Quaternion::PosAxis(qua, fonts_[j].relative_[i]);

			//座標
			fonts_[j].vertices_[i].pos = VAdd(fonts_[j].center_, fonts_[j].relative_[i]);
		}

		//回転量の加算
		fonts_[j].rots_ += deg_;

		//ステートごとの処理
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
				fonts_[j].rots_ = 0.0f;		//回転量初期化
				fonts_[j].state_ = ROT_STATE::NONE;

				//ラストの処理を終えたら
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
	//メッシュテキスト
	for (int j = 0; j < MESH_FONT_NUM; j++)
	{
		VERTEX3D vertices1[VERTICES] = { fonts_[j].vertices_[0],fonts_[j].vertices_[1], fonts_[j].vertices_[2] };
		VERTEX3D vertices2[VERTICES] = { fonts_[j].vertices_[1],fonts_[j].vertices_[3], fonts_[j].vertices_[2] };

		DrawPolygon3D(vertices1, 1, *imgAlphabet_[0], true); // 三角形1
		DrawPolygon3D(vertices2, 1, *imgAlphabet_[0], true); // 三角形2
	}
}
