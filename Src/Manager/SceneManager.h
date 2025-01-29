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

// 推奨しませんが、どうしても使いたい方は
#define mainCamera SceneManager::GetInstance().GetCamera().lock()

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

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME
	};
	
	void Init(void);
	void Init3D(void);

	/// <summary>
	/// 先頭の（Updataが呼ばれる）シーンを切り替える
	/// </summary>
	/// <param name="scene">切り替え先のシーン</param>
	void CreateScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// すべてのシーンを切り替える
	/// </summary>
	/// <param name="scene">切り替え先のシーン</param>
	void ChangeAllScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// シーンをプッシュする。スタックの数が増える
	/// 一番上のシーンのUpdataしか呼ばれません。
	/// </summary>
	/// <param name="scene">積むシーン</param>
	//void PushScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// スタックの頭のシーンを削除する。
	/// ただし、スタック上にシーンが一つしかない場合は、削除しない。
	/// </summary>
	//void PopScene();

	void Update(InputManager& ins);
	void Draw(void);

	// リソースの破棄
	void Destroy(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID(void);

	// デルタタイムの取得
	float GetDeltaTime(void) const;

	// 経過時間の取得
	const float& GetTotalTime(void) const { return totalTime_; }

	// メインスクリーンの取得
	const int& GetMainScreen(void) const { return mainScreen_; }

	// カメラの取得
	std::weak_ptr<Camera> GetCamera(void) const;

	//フェードイン開始
	void StartFadeIn(void);

	//フェードカラーの指定
	void SetFadeColor(unsigned int color);

	//描画スクリーンのセット
	void SetDrawingScreen(const int& screenID);

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(SceneManager);

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// フェード
	std::unique_ptr<Fader> fader_;

	// カメラ
	std::shared_ptr<Camera>  camera_;

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

	//スクリーン座標
	Vector2 screenPos_;

	//スクリーン振幅
	float amplitude_;

	//フレーム
	int frame_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// デストラクタも同様
	~SceneManager(void) = default;

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade(void);

};