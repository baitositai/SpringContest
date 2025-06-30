#pragma once
#include "../framework.h"
#include "SceneBase.h"

class SelectScene : public SceneBase
{
public:

	//音量
	static constexpr int VOLUME = 70;

	//描画位置
	static constexpr int ON_POS_X = 350;
	static constexpr int ON_POS_Y = 520;
	static constexpr int OFF_POS_X = 500;
	static constexpr int OFF_POS_Y = 520;
	static constexpr int SPEECH_POS_X = 875;
	static constexpr int SPEECH_POS_Y = 520;

	// 上下揺れの振幅（大きさ）
	static constexpr float AMPLITUDE = 10.0f;

	// 上下揺れの周期（揺れる速さ）
	static constexpr float PERIOD = 0.05f;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager"></param>シーン管理クラス
	SelectScene(SceneManager& manager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <param name=""></param>
	~SelectScene(void) = default;

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

	// 更新関数
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//描画関数 
	void LoadingDraw();		//読み込み中描画
	void NormalDraw();		//ゲーム中描画

	//プレイヤーの自動攻撃の有無を調べる
	void CheckPlayerTackle();

	//画像
	int image_;
	int imgSelect_;
	int imgSpeech_;

	//更新用ステップ
	float step_;

};

