#pragma once
#include "SceneBase.h"
#include "../framework.h"
#include "../Common/Vector2.h"
#include "../Manager/ResourceManager.h"

class TitlePlayer;
class TitleMesh;
class TitleStage;
class SkyDome;

class TitleScene : public SceneBase
{

public:

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

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager"></param>シーン管理クラス
	TitleScene(SceneManager& manager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <param name=""></param>
	~TitleScene(void) = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="ins"></param>入力管理クラス
	void Update(InputManager& ins) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 解放
	/// </summary>
	void Release() override;

	/// <summary>
	/// 共通描画
	/// </summary>
	void CommonDraw() override;

private:	

	//タイトル背景
	int imgTitle_;

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

	//ステージ
	std::unique_ptr<TitleStage> stage_;

	//スカイドーム
	std::unique_ptr<SkyDome> sky_;
};