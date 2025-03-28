#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "Resource.h"

// オムレツ走る画像
constexpr int ALPHABET_NUM_X = 10;
constexpr int ALPHABET_NUM_Y = 6;
constexpr int ALPHABET_IMG_SIZE_X = 320;
constexpr int ALPHABET_IMG_SIZE_Y = 192;
constexpr int ALPHABET_SIZE_X = ALPHABET_IMG_SIZE_X / ALPHABET_NUM_X;
constexpr int ALPHABET_SIZE_Y = ALPHABET_IMG_SIZE_Y / ALPHABET_NUM_Y;

//プレイヤーアイコン
constexpr int PLAYER_ICONS_NUM_X = 1;
constexpr int PLAYER_ICONS_NUM_Y = 2;
constexpr int PLAYER_ICONS_IMG_SIZE_X = 128;
constexpr int PLAYER_ICONS_IMG_SIZE_Y = 256;
constexpr int PLAYER_ICONS_SIZE = 128;

//数字画像
constexpr int NUMBERS_NUM_X = 5;
constexpr int NUMBERS_NUM_Y = 2;
constexpr int NUMBERS_IMG_SIZE_X = 640;
constexpr int NUMBERS_IMG_SIZE_Y = 256;
constexpr int NUMBERS_SIZE = 128;

//数字2画像
constexpr int NUMBERS2_NUM_X = 5;
constexpr int NUMBERS2_NUM_Y = 2;
constexpr int NUMBERS2_IMG_SIZE_X = 210;
constexpr int NUMBERS2_IMG_SIZE_Y = 84;
constexpr int NUMBERS2_SIZE = 42;

//プレイヤーUI
constexpr int PLAYER_UI_NUM_X = 1;
constexpr int PLAYER_UI_NUM_Y = 2;
constexpr int PLAYER_UI_IMG_SIZE_X = 384;
constexpr int PLAYER_UI_IMG_SIZE_Y = 192;
constexpr int PLAYER_UI_SIZE_X = PLAYER_UI_IMG_SIZE_X / PLAYER_UI_NUM_X;
constexpr int PLAYER_UI_SIZE_Y = PLAYER_UI_IMG_SIZE_Y / PLAYER_UI_NUM_Y;

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
		NUMBER,
		NUMBER2,
		PLAYER_UI,
		TIMER_UI,
		WIN_UI,
		TITLE_LOGO,
		DRAW,

		//UI画像
		POWER_UI,
		LIFE_UI,
		SCORE_UI,
		HINDER,
		HINDER_GAGE,
		PLAYER_ICONS,
		LIFE,
		POWER,
		TITLE,
		TITLE_UI,
		TITLE_BACKGROUND,

		//モデル
		PLAYER,
		STAGE,
		SKY_DOME,
		ENEMY,
		BOMB,
		HEART,
		POTION,

		//エフェクト
		TACKLE_EFK,
		STAR_DUST_EFK,

		//音楽
		TITLE_BGM,
		SELECT_BGM,
		GAMEBGM1,
		GAMEBGM2,
		CHANGE_SCENE_SE,
		SWITCH_ON_SE,
		SWITCH_OFF_SE,
		TACKLE_SE,
		ITEM_GET_SE,
		DAMAGE_SE,
		COUNT_DOWN_SE,
		COUNT_3,
		COUNT_2,
		COUNT_1,
		COUNT_0,
		GO_SE,
		CLEAR_SE,
		JUMP_SE,
		BLAST_SE,
		ENEMY_DAMAGE_SE
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

