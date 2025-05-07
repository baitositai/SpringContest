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

//操作説明
//プレイヤーUI
constexpr int EXPLAN_NUM_X = 2;
constexpr int EXPLAN_NUM_Y = 1;
constexpr int EXPLAN_IMG_SIZE_X = 240;
constexpr int EXPLAN_IMG_SIZE_Y = 160;
constexpr int EXPLAN_SIZE_X = EXPLAN_IMG_SIZE_X / EXPLAN_NUM_X;
constexpr int EXPLAN_SIZE_Y = EXPLAN_IMG_SIZE_Y / EXPLAN_NUM_Y;

//エフェクト
constexpr int EFK_NUM_X = 6;
constexpr int EFK_NUM_Y = 5;
constexpr int EFK_IMG_SIZE_X = 1536;
constexpr int EFK_IMG_SIZE_Y = 1280;
constexpr int EFK_SIZE = 256;

//ゲットエフェクト
constexpr int GET_EFK_NUM_X = 8;
constexpr int GET_EFK_NUM_Y = 5;
constexpr int GET_EFK_IMG_SIZE_X = 2048;
constexpr int GET_EFK_IMG_SIZE_Y = 1280;
constexpr int GET_EFK_SIZE = 256;

//妨害オブジェクト
constexpr int HINDER_NUM_X = 4;
constexpr int HINDER_NUM_Y = 1;
constexpr int HINDER_SIZE = 96;
constexpr int HINDER_IMG_SIZE_X = HINDER_NUM_X * HINDER_SIZE;
constexpr int HINDER_IMG_SIZE_Y = HINDER_NUM_Y * HINDER_SIZE;

//タイトルUI
constexpr int TITLE_UI_NUM_X = 9;
constexpr int TITLE_UI_NUM_Y = 1;
constexpr int TITLE_UI_SIZE = 100;
constexpr int TITLE_UI_IMG_SIZE_X = TITLE_UI_SIZE * TITLE_UI_NUM_X;
constexpr int TITLE_UI_IMG_SIZE_Y = TITLE_UI_SIZE * TITLE_UI_NUM_Y;


class ResourceManager :
	public StaticSingleton<ResourceManager>
{

public:

	// リソース名
	enum class SRC
	{
		//画像
		PLAYER_SHADOW,
		NUMBER,
		NUMBER2,
		PLAYER_UI,
		TIMER_UI,
		WIN_UI,
		TITLE_LOGO,
		DRAW,
		HINDER_OBJS,

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
		TACKLE_GAGE,
		SPEED_UP,
		TACKLE_SELECT,
		EXPLAN,

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
		HIT_EFK,
		EXPLOSION_EFK,
		GET_EFK,

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
		ENEMY_DAMAGE_SE,
		SPEED_UP_SE,
		HINDER_SE,

		//動画
		MOVIE,
	};

	// 初期化
	void Init();

	// 解放(シーン切替時に一旦解放)
	void Release();

	// リソースの完全破棄
	void Destroy();

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
	ResourceManager();

	// デストラクタも同様
	~ResourceManager() = default;

	// 内部ロード
	Resource& _Load(SRC src);

};

