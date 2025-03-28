#pragma once
#include "SceneBase.h"
#include "../framework.h"
#include "../Common/Vector2.h"
#include "../Manager/ResourceManager.h"
class TitlePlayer;

class TitleScene : public SceneBase
{

public:

	enum class ROT_STATE
	{
		NONE,
		START,	//開始
		HALF,	//半回転済み
	};

	//タイトルフォントサイズ
	static constexpr int MES_FONT_SIZE = 28;

	//頂点数
	static constexpr int VERTEXS = 4;

	//フォントサイズ
	static constexpr float FONT_SIZE = 50;
	static constexpr float FONT_SIZE_H = FONT_SIZE / 2;

	//テキストの間隔
	static constexpr float TEXT_INTERVEL = 40;

	//メッシ用フォント数
	static constexpr int  MESH_FONT_NUM =9;

	//アルファベット
	static constexpr int ALPHABET_IMG_NUM = ALPHABET_NUM_X * ALPHABET_NUM_Y;

	//音量
	static constexpr int VOLUME = 70;

	// コンストラクタ
	TitleScene(SceneManager& manager);

	// デストラクタ
	~TitleScene(void);

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& ins) override;
	void Draw(void) override;
	void Release(void) override;

	//共通描画
	void CommonDraw() override;

private:	
	// テキスト画像
	int* imgTexts_[ALPHABET_IMG_NUM];

	//タイトル背景
	int imgTitle_;

	//タイトルUI
	int imgTitleUI_;

	//アルファ
	int alpha_;

	//フェード値
	int fade_;

	//タイトル背景
	int imgTitleBackGround_;

	// メッセージフォント
	int mesFont_;

	//回転開始カウント
	int cnt_;

	//回転用角度
	float deg_;

	//拡大縮小量
	float ex_;

	//拡大縮小スピード
	float exSpeed_;

	//相対座標
	//VECTOR rPos_[VERTEXS];

	// メッシュ用情報
	struct MeshText
	{
		float rots_;					//回転量

		ROT_STATE state_;				//回転状態

		Vector2 fontNumber_;			//画像のフォント管理番号

		VECTOR center_;					//メッシュ中央位置

		VECTOR relative_[VERTEXS];		//相対座標

		VERTEX3D vertices_[VERTEXS];	//メッシュ頂点情報
	};

	// メッシュのフォント情報
	MeshText fonts_[MESH_FONT_NUM];

	// 更新関数
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	// 描画関数
	void LoadingDraw(void);
	void NormalDraw(void);

	// メッシュ初期化
	void MeshInit();

	// メッシュ更新
	void MeshUpdate();

	void Fade();

	//インスタンス生成
	std::unique_ptr<TitlePlayer> titlePlayer_;

};