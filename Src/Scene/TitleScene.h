#pragma once
#include "SceneBase.h"
#include "../framework.h"
#include "../Common/Vector2.h"
#include "../Manager/ResourceManager.h"

class TitlePlayer;
class TitleMesh;

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

	//音量
	static constexpr int VOLUME = 70;

	//シーン遷移秒数
	static constexpr int CHANGE_SCENE_SECOND = 180;

	//ロゴ位置
	static constexpr int LOGO_POS_X = 525;
	static constexpr int LOGO_POS_Y = 200;

	//ロゴ拡大率
	static constexpr float LOGO_RATE = 0.5f;

	// コンストラクタ
	TitleScene(SceneManager& manager);

	// デストラクタ
	~TitleScene(void) = default;

	void Load() override;
	void Init() override;
	void Update(InputManager& ins) override;
	void Draw() override;
	void Release() override;

	//共通描画
	void CommonDraw() override;

private:	

	//タイトル背景
	int imgTitle_;

	//タイトル背景
	int imgTitleBackGround_;

	// メッセージフォント
	int mesFont_;

	//更新用ステップ
	float changeSceneStep_;

	// 更新関数
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	// 描画関数
	void LoadingDraw();
	void NormalDraw();

	//プレイヤー
	std::unique_ptr<TitlePlayer> titlePlayer_;

	//メッシュ
	std::unique_ptr<TitleMesh> titleMesh_;
};