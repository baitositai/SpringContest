#pragma once
#include "../framework.h"
#include "SceneBase.h"


class MovieScene : public SceneBase
{
public:

	//ムービーの状態
	enum class MOVIE_STATE
	{
		NONE,
		START,	//カウントダウン
		PLAY,	//プレイ
		RESULT,	//結果
	};

	//ムービーの初期位置
	static constexpr VECTOR DEFAULT_PLAYER_POS = { 0,0,0 };

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager"></param>シーン管理クラス
	MovieScene(SceneManager& manager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MovieScene() = default;

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

	//動画
	int movie_;	//動画のID

	//更新関数
	void LoadingUpdate(InputManager& ins);	//読み込み中処理
	void NormalUpdate(InputManager& ins);	//ゲーム中処理

	//描画関数 
	void LoadingDraw();		//読み込み中描画
	void NormalDraw();		//ゲーム中描画(基本はここに書いてね)

};

