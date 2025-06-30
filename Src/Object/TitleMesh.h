#pragma once
#include <DxLib.h>
#include "../Common/Vector2.h"

class TitleMesh
{

public:	
	
	//回転状態
	enum class ROT_STATE
	{
		NONE,
		START,	//開始
		HALF,	//半回転済み
	};

	//回転用角度
	static constexpr float DEG = 2.0f;

	//拡大縮小スピード
	static constexpr float EX_SPEED = 0.2f;

	//頂点数
	static constexpr int VERTEXS = 4;

	//テキストの間隔
	static constexpr float TEXT_INTERVEL = 40;

	//フォントサイズ
	static constexpr float FONT_SIZE = 50;
	static constexpr float FONT_SIZE_H = FONT_SIZE / 2;

	//メッシ用フォント数
	static constexpr int  MESH_FONT_NUM = 9;

	//アルファベット
	static constexpr int ALPHABET_IMG_NUM = 9;

	//頂点数
	static constexpr int VERTICES = 3;

	//メッシュの回転処理のインターバール
	static constexpr int MESH_UPD_INTERVAL = 20;

	//メッシュのZ軸の移動量
	static constexpr float MESH_MOVE_Z = -1.5f;

	//回転
	static constexpr float ROT_STATE_START = 90.0f;
	static constexpr float ROT_STATE_HALF = 180.0f;	
	
	//1文字目の初期座標
	static constexpr VECTOR FIRST_POS = { 370,400,-100 };

	//色
	static constexpr COLOR_U8 COLOR_LT = { 255, 255, 255, 255 };//左上
	static constexpr COLOR_U8 COLOR_RT = { 255, 0, 255, 255 };	//右上
	static constexpr COLOR_U8 COLOR_LB = { 255, 255, 0, 255 };	//左下
	static constexpr COLOR_U8 COLOR_RB = { 255, 255, 0, 255 };	//右下

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleMesh();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleMesh() = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//アルファベット画像
	int* imgAlphabet_[ALPHABET_IMG_NUM];

	//回転開始カウント
	int cnt_;

	//回転用角度
	float deg_;

	//拡大縮小量
	float ex_;

	//拡大縮小スピード
	float exSpeed_;

	// メッシュ用情報
	struct MeshText
	{
		//回転量
		float rots_ = -1.0f;

		//回転状態
		ROT_STATE state_ = ROT_STATE::NONE;

		//画像のフォント管理番号
		Vector2 fontNumber_ = { -1,-1 };

		//メッシュ中央位置
		VECTOR center_ = { -1,-1,-1 };

		//相対座標
		VECTOR relative_[VERTEXS] =
		{ { -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 } };

		//メッシュ頂点情報
		VERTEX3D vertices_[VERTEXS] =
		{ { -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 } };
	};

	// メッシュのフォント情報
	MeshText fonts_[MESH_FONT_NUM];

};

