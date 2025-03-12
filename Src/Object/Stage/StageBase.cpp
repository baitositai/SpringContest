#include "StageBase.h"
#include "../../Manager/ScrollManager.h"

StageBase::StageBase(void)
{
	type_ = STAGE_TYPE::STAGE;
}

StageBase::~StageBase(void)
{
}

void StageBase::Init(void)
{

	//const char* FILENAME[static_cast<int>(STAGE_TYPE::MAX)]
	//{
	//	"Data/Model/Stage/stage.mv1"
	//	/*"Data/Model/Stage/stageRight.mv1",
	//	"Data/Model/Stage/stageLeft.mv1"*/
	//};

	//for (int pl = 0; pl < static_cast<int>(STAGE_TYPE::MAX); pl++)
	//{
	//	// ステージを読み込む
	//	stage_[pl] = MV1LoadModel(FILENAME[pl]);
	//	if (stage_[pl] == -1)
	//	{
	//		return;
	//	}
	//}

	//transform_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::STAGE));

	//type_ = STAGE_TYPE::STAGE;
	//transform_.pos.x = 0;
	//transform_.pos.y = 0;
	//transform_.pos.z = 0;
	//transform_.Update();

	//transform_.scl = { 1,1,1 };

}

void StageBase::Update(void)
{
	// 画面に映る位置に３Ｄモデルを移動
	//MV1SetPosition(stage_[static_cast<int>(type_)], VGet(transform_.pos.x, transform_.pos.y, transform_.pos.z));

	//スクロール
	auto& scr = ScrollManager::GetInstance();
	//Z値を減らしていく
	transform_.pos.z -= scr.GetScrollSpeed();
	transform_.Update();
}

void StageBase::Draw(void)
{
	// ３Ｄモデルの描画
	//MV1DrawModel(stage_[static_cast<int>(type_)]);
	MV1DrawModel(transform_.modelId);
}

void StageBase::Release(void)
{
	for (int i = 0; i < static_cast<int>(STAGE_TYPE::MAX);i++)
	{
		// モデルハンドルの削除
		MV1DeleteModel(stage_[i]);
	}
}

Transform StageBase::GetTransform(void)
{
	return transform_;
}

void StageBase::SetPos(Transform trans)
{
	transform_.pos = trans.pos;
}