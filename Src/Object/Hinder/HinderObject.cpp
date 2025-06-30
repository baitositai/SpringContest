#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "HinderObject.h"

HinderObject::HinderObject()
{
	//初期化
	objs_.clear();

	int i = -1;
	imgs_ = &i;
}

void HinderObject::Load()
{
	//画像読み込み
	imgs_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::HINDER_OBJS).handleIds_;
}

void HinderObject::Init()
{
	objs_.clear();
}

void HinderObject::Update()
{
	//中身がない場合処理を抜ける
	if (objs_.empty()) { return; }

	//位置更新
	for (Object& omu : objs_)
	{
		//移動
		omu.pos_.x += omu.vec_.x;
		omu.pos_.y += omu.vec_.y;

		// 画面端での反射処理
		if (omu.pos_.x <= 0 || omu.pos_.x + IMG_SIZE >= Application::SCREEN_HALF_X)
		{
			Reflect(omu.vec_, 1.0f, 0.0f);  // 垂直な壁 (法線: x方向)
			// 画面内に押し戻す
			omu.pos_.x += static_cast<int>(omu.vec_.x * 0.1f);
		}
		if (omu.pos_.y <= 0 || omu.pos_.y + IMG_SIZE >= Application::SCREEN_SIZE_Y)
		{
			Reflect(omu.vec_, 0.0f, 1.0f);  // 水平な壁 (法線: y方向)
			// 画面内に押し戻す
			omu.pos_.y += static_cast<int>(omu.vec_.y * 0.1f);
		}

		// ベクトルの絶対値が小さすぎるときに再ランダム化
		double magnitude = sqrt(omu.vec_.x * omu.vec_.x + omu.vec_.y * omu.vec_.y);
		if (magnitude < 0.01f) 
		{
			float angle = static_cast<float>(GetRand(RAND_RANGE) * DX_PI / 180.0f);
			omu.vec_.x = static_cast<int>(cosf(angle) * SPEED);
			omu.vec_.y = static_cast<int>(sinf(angle) * SPEED);
		}
	}
}

void HinderObject::Draw()
{
	//中身がない場合処理を抜ける
	if (objs_.empty()) { return; }

	for (Object& omu : objs_)
	{
		//描画
		DrawGraph(
			omu.pos_.x,
			omu.pos_.y,
			imgs_[omu.type_],
			true);
	}
}

void HinderObject::AddObject(const int num)
{
	//初期化
	for (int i = 0; i < num; i++)
	{
		Object omu;
		//初期位置(ランダム)
		omu.pos_.x = GetRand(Application::SCREEN_HALF_X - HINDER_SIZE -1);
		omu.pos_.y = GetRand(Application::SCREEN_SIZE_Y - HINDER_SIZE -1);
		// 角度をラジアンに変換して速度ベクトルに変換
		omu.vec_.x = static_cast<int>(SPEED * cos(ANGLE * DX_PI / 180.0f));
		omu.vec_.y = static_cast<int>(SPEED * sin(ANGLE * DX_PI / 180.0f));
		//画像種類を決める
		omu.type_ = GetRand(HINDER_NUM_X * HINDER_NUM_Y - 1);
		//追加
		objs_.emplace_back(omu);
	}
}

void HinderObject::Reflect(Vector2& vec, float nx, float ny)
{
	float dot = vec.x * nx + vec.y * ny;

	//反射ベクトルの計算
	vec.x = static_cast<int>(vec.x - 2.0f * dot * nx);
	vec.y = static_cast<int>(vec.y - 2.0f * dot * ny);
}
