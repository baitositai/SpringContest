#pragma once
#include "../framework.h"
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Common/Vector2.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "Camera.h"

class SceneBase;
class InputManager;
class Fader;
class Camera;

class SceneManager : public StaticSingleton<SceneManager>
{

public:

	//FPS値
	static constexpr float DEFAULT_FPS = 60.0f;

	//重力
	static constexpr float GRAVITY = 9.81f;

	//デルタタイム
	static constexpr float DELTA_TIME = 1.0f / 60.0f;

	//最大プレイ人数
	static constexpr int PLAYER_MAX = 2;

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		MOVIE,
		SELECT,
		GAME
	};

	//人数管理
	enum class MODE
	{
		NONE,
		MARASON,
		VS,
	};
	
	void Init(void);
	void Init3D(void);

	/// <summary>
	/// 先頭の（Updateが呼ばれる）シーンを切り替える
	/// </summary>
	/// <param name="scene">切り替え先のシーン</param>
	void CreateScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// すべてのシーンを切り替える
	/// </summary>
	/// <param name="scene">切り替え先のシーン</param>
	void ChangeAllScene(std::shared_ptr<SceneBase> scene);

	void Update(InputManager& ins);
	void Draw(void);

	// リソースの破棄
	void Destroy(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID();

	// デルタタイムの取得
	float GetDeltaTime() const;

	// 経過時間の取得
	const float& GetTotalTime() const { return totalTime_; }

	// メインスクリーンの取得
	const int& GetMainScreen() const { return mainScreen_; }

	// カメラの取得
	std::vector<std::shared_ptr<Camera>> GetCameras() const;

	//フェードイン開始
	void StartFadeIn();

	//フェードカラーの指定
	void SetFadeColor(unsigned int color);

	//描画スクリーンのセット
	void SetDrawingScreen(const int screenID);

	//描画スクリーンのカウントを返す
	inline const int GetScreenCount()const { return screenCnt_; }

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(SceneManager);

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// フェード
	std::unique_ptr<Fader> fader_;

	// カメラ
	std::vector<std::shared_ptr<Camera>> cameras_;

	// 現在実行中のシーン
	std::list<std::shared_ptr<SceneBase>> scenes_;

	// シーン遷移中判定
	bool isSceneChanging_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	//経過時間
	float totalTime_;

	//メインスクリーン
	int mainScreen_;
	int halfScreen_[PLAYER_MAX];

	//スクリーン座標
	Vector2 screenPos_;

	//スクリーン振幅
	float amplitude_;

	//フレーム
	int frame_;

	//スクリーンカウント
	int screenCnt_;

	//描画用
	std::function<void(void)> drawFunc_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager();
	// デストラクタも同様
	~SceneManager() = default;

	// デルタタイムをリセットする
	void ResetDeltaTime();

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade();

	// 通常の描画
	void NormalDraw();

	// VS用の描画
	void VSPlayDraw();

};