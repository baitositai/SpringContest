#include <DxLib.h>
#include <iostream>
#include <cassert> 
#include "Resource.h"

Resource::Resource()
{
	type_ = TYPE::NONE;
	path_ = "";

	numX_ = -1;
	numY_ = -1;
	sizeX_ = -1;
	sizeY_ = -1;

	handleId_ = -1;
	handleIds_ = nullptr;
}

Resource::Resource(TYPE type, const std::string& path)
{
	type_ = type;
	path_ = path;

	numX_ = -1;
	numY_ = -1;
	sizeX_ = -1;
	sizeY_ = -1;

	handleId_ = -1;
	handleIds_ = nullptr;
}

Resource::Resource(TYPE type, const std::string& path, int numX, int numY, int sizeX, int sizeY)
{
	type_ = type;
	path_ = path;
	numX_ = numX;
	numY_ = numY;
	sizeX_ = sizeX;
	sizeY_ = sizeY;

	handleId_ = -1;
	handleIds_ = nullptr;
}

Resource::~Resource()
{
}

void Resource::Load()
{
	switch (type_)
	{
	case Resource::TYPE::IMG:
		// 画像
		handleId_ = LoadGraph(path_.c_str());
		break;

	case Resource::TYPE::IMGS:
		// 複数画像
		handleIds_ = new int[numX_ * numY_];
		LoadDivGraph(
			path_.c_str(),
			numX_ * numY_,
			numX_, numY_,
			sizeX_, sizeY_,
			&handleIds_[0]);
		break;

	case Resource::TYPE::MODEL:
		// モデル
		handleId_ = MV1LoadModel(path_.c_str());
		break;

	case Resource::TYPE::EFFEKSEER:
 		//handleId_ = LoadEffekseerEffect(path_.c_str());
		break;

	case Resource::TYPE::FONT:
		//フォント
		handleId_ = AddFontResourceEx(path_.c_str(), FR_PRIVATE, NULL);
		break;

	case Resource::TYPE::SOUND:
		//サウンド
		handleId_ = LoadSoundMem(path_.c_str());
	}

	//リソースが読み込めたか確認
	if (type_ == Resource::TYPE::IMGS) {
		for (int i = 0; i < numX_ * numY_; i++) {
			assert(handleIds_[i] != -1); // 各スプライトの読み込みが成功してるか確認
		}
	}
	else {
		assert(handleId_ != -1);
	}
}

void Resource::Release()
{
	switch (type_)
	{
	case Resource::TYPE::IMG:
		DeleteGraph(handleId_);
		break;

	case Resource::TYPE::IMGS:
	{
		int num = numX_ * numY_;
		for (int i = 0; i < num; i++)
		{
			DeleteGraph(handleIds_[i]);
		}
		delete[] handleIds_;
	}
	break;

	case Resource::TYPE::MODEL:
	{
		MV1DeleteModel(handleId_);
		auto ids = duplicateModelIds_;

		// デバッグ出力
		std::cout << "duplicateModelIds_ size: " << ids.size() << std::endl;
		for (auto id : ids)
		{
			std::cout << "Deleting model ID: " << id << std::endl;
			MV1DeleteModel(id);
		}
	}
	break;

	case Resource::TYPE::EFFEKSEER:
		//DeleteEffekseerEffect(handleId_);
		break;

	case Resource::TYPE::FONT:
		RemoveFontResourceEx(path_.c_str(), FR_PRIVATE, NULL);
		break;

	case Resource::TYPE::SOUND:
		DeleteSoundMem(handleId_);
		break;
	}


}

void Resource::CopyHandle(int* imgs)
{

	if (handleIds_ == nullptr)
	{
		return;
	}

	int num = numX_ * numY_;
	for (int i = 0; i < num; i++)
	{
		imgs[i] = handleIds_[i];
	}

}
