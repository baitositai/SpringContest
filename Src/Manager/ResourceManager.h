#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "../Application.h"
#include "Resource.h"

// オムレツ走る画像
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

	// リソース名
	enum class SRC
	{
		//画像
		ALPHABET,
		PLAYER_SHADOW,

		//モデル
		PLAYER,
		SKY_DOME,
		ENEMY,
		STAGE,
		STAGERIGHT,
		STAGELEFT
	};

	// 初期化
	void Init(void);

	// 解放(シーン切替時に一旦解放)
	void Release(void);

	// リソースの完全破棄
	void Destroy(void);

	// リソースのロード
	Resource& Load(SRC src);

	// リソースの複製ロード(モデル用)
	int LoadModelDuplicate(SRC src);

private:

	//シングルトンの生成
	THIS_CLASS_IS_STATIC_SINGLETON(ResourceManager);

	// リソース管理の対象
	std::map<SRC, std::unique_ptr<Resource>> resourcesMap_;

	// 読み込み済みリソース
	std::map<SRC, Resource&> loadedMap_;	
	
	Resource dummy_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);

	// デストラクタも同様
	~ResourceManager(void) = default;

	// 内部ロード
	Resource& _Load(SRC src);

};

