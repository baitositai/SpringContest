#pragma once
#include "../framework.h"
#include "../Application.h"

class SceneManager;
class InputManager;

//最低ローディング時間
constexpr float LOADING_TIME = 1.0f;

//フォントサイズ
constexpr int LOAD_FONT_SIZE = 28;

//ローディング
constexpr int COMMA_MAX_NUM = 5;			//「now loading......」のコンマの数
constexpr float COMMA_TIME = 0.3f;			//「now loading......」のコンマ数を増やす時間
constexpr int LOADING_STRING_POS_X = Application::SCREEN_SIZE_X - 200;	//「now loading......」の座標X
constexpr int LOADING_STRING_POS_Y = Application::SCREEN_SIZE_Y - LOAD_FONT_SIZE - 15;	//「now loading......」の座標Y

class SceneBase
{

public:

	//シーンマネージャー
	SceneManager& sceneManager_;

	// コンストラクタ
	SceneBase(SceneManager& scene);

	// デストラクタ
	virtual ~SceneBase(void) = 0;

	// 読み込み処理
	virtual void Load(void) = 0;

	// 初期化処理
	virtual void Init(void) = 0;

	// 更新ステップ
	virtual void Update(InputManager& input) = 0;

	// 描画処理
	virtual void Draw(void) = 0;

	// 解放処理
	virtual void Release(void) = 0;

protected:

	//ローディング中描画フォント
	int loadFont_;

	//ローディング経過時間
	float loadingTime_;

	std::function<void(InputManager&)> updataFunc_;
	std::function<void(void)> drawFunc_;
	
	//「now loading......」の描画
	void DrawNowLoading(void);

};
