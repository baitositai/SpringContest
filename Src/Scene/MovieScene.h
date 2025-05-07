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

	// コンストラクタ
	MovieScene(SceneManager& manager);

	// デストラクタ
	~MovieScene() = default;

	void Load() override;
	void Init() override;
	void Update(InputManager& input) override;
	void Draw() override;
	void Release() override;

	//共通描画
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

