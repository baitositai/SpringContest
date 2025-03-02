#include <DxLib.h>
#include "StageBase.h"

StageBase::StageBase(void)
{
	type_ = STAGE_TYPE::STAGE;
}

StageBase::~StageBase(void)
{
}

void StageBase::Init(void)
{

	const char* FILENAME[static_cast<int>(STAGE_TYPE::MAX)]
	{
		"Data/Model/Stage/stage.mv1"
		/*"Data/Model/Stage/stageRight.mv1",
		"Data/Model/Stage/stageLeft.mv1"*/
	};

	for (int pl = 0; pl < static_cast<int>(STAGE_TYPE::MAX); pl++)
	{
		// ステージを読み込む
		stage_[pl] = MV1LoadModel(FILENAME[pl]);
		if (stage_[pl] == -1)
		{
			return;
		}
	}

	type_ = STAGE_TYPE::STAGE;
	pos_.x = 1000;
	pos_.y = -2000;
	pos_.z = 2000;

}

void StageBase::Update(void)
{
	// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(stage_[static_cast<int>(type_)], VGet(pos_.x, pos_.y, pos_.z));
}

void StageBase::Draw(void)
{
	// ３Ｄモデルの描画
	MV1DrawModel(stage_[static_cast<int>(type_)]);
}

void StageBase::Release(void)
{
	for (int i = 0; i < static_cast<int>(STAGE_TYPE::MAX);i++)
	{
		// モデルハンドルの削除
		MV1DeleteModel(stage_[i]);
	}
}

void StageBase::SetPos(IntVector3 pos)
{
	pos_ = pos;
}