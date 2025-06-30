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

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene"></param>シーン管理クラス
	SceneBase(SceneManager& scene);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SceneBase() = 0;

	/// <summary>
	/// 読みこみ
	/// </summary>
	virtual void Load() = 0;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input"></param>入力管理クラス
	virtual void Update(InputManager& input) = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 画面共通描画
	/// </summary>
	virtual void CommonDraw() = 0;

	/// <summary>
	/// 解放
	/// </summary>
	virtual void Release() = 0;

protected:

	//ローディング中描画フォント
	int loadFont_;

	//ローディング経過時間
	float loadingTime_;

	//更新を管理
	std::function<void(InputManager&)> updateFunc_;

	//描画ヲ管理
	std::function<void(void)> drawFunc_;
	
	//「now loading......」の描画
	void DrawNowLoading(void);

};
