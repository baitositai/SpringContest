#pragma once
#include "framework.h"

class FpsControl;

class Application
{

public:

	//※16:9にする場合 1280×720
	//※4:3にする場合  1024×768
	// スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = static_cast<int>(1024 * 1);
	static constexpr int SCREEN_SIZE_Y = static_cast<int>(768 * 1);
	
	// スクリーンサイズハーフ
	static constexpr int SCREEN_HALF_X = SCREEN_SIZE_X / 2;
	static constexpr int SCREEN_HALF_Y = SCREEN_SIZE_Y / 2;

	//カラービット深度
	static constexpr int COLOR_BIT_DEPTH = 32;

	// データパス関連
	//-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;
	static const std::string PATH_FONT;
	static const std::string PATH_TEXT;
	static const std::string PATH_SOUND;
	static const std::string PATH_MOVIE;
	//-------------------------------------------

	// 明示的にインステンスを生成する
	static void CreateInstance();

	// 静的インスタンスの取得
	static Application& GetInstance();

	// 初期化
	void Init();

	// ゲームループの開始
	void Run();

	// リソースの破棄
	void Destroy();

	// 初期化成功／失敗の判定
	bool IsInitFail() const;

	// 解放成功／失敗の判定
	bool IsReleaseFail() const;

private:

	// 静的インスタンス
	static Application* instance_;

	// 初期化失敗
	bool isInitFail_;

	// 解放失敗
	bool isReleaseFail_;

	//FPS
	std::unique_ptr<FpsControl> fps_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	Application();

	// コピーコンストラクタも同様
	Application(const Application&);

	// デストラクタも同様
	~Application() = default;

};