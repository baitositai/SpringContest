#pragma once
#include "../framework.h"
#include "SceneBase.h"

class Player;
class ObjectManager;
class TimeCount;

class GameScene : public SceneBase
{
public:

	//ゲーム開始カウントダウン
	static constexpr float COUNTDOWN = 3.0f;

	//ゲーム中の状態
	enum class STATE
	{
		START,	//カウントダウン
		PLAY,	//プレイ
		REZALT,	//結果
	};

	//カメラ位置
	static constexpr VECTOR LOCAL_CAMERA_POS = { 0, 150, -200 };

	// コンストラクタ
	GameScene(SceneManager& manager);

	// デストラクタ
	~GameScene(void) = default;

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& input) override;
	void Draw(void) override;
	void Release(void) override;

private:	

	//開始カウント
	float strCnt_;

	//状態
	STATE state_;

	// 状態管理(状態遷移時初期処理)
	std::map<STATE, std::function<void(void)>> stateChanges_;

	// 状態管理(更新ステップ)
	std::function<void(void)> stateGameUpdate_;
	std::function<void(void)> stateGameDraw_;

	//インスタンス生成
	std::shared_ptr<Player> player_;
	std::unique_ptr<ObjectManager> objs_;
	std::unique_ptr<TimeCount> time_;

	//更新関数
	void LoadingUpdate(InputManager& ins);	//読み込み中処理
	void NormalUpdate(InputManager& ins);	//ゲーム中処理
	
	//描画関数 
	void LoadingDraw(void);		//読み込み中描画
	void NormalDraw(void);		//ゲーム中描画

	//状態遷移
	void ChangeState(STATE state);
	void ChangeStart(void);
	void ChangePlay(void);
	void ChangeRezalt(void);

	//更新ステップ
	void StartUpdate(void);
	void PlayUpdate(void);
	void RezaltUpdate(void);

	//描画ステップ
	void StartDraw();
	void PlayDraw();
	void RezaltDraw();

	//衝突判定
	void Collision();

	//ゲームオーバー判定
	void CheckGameOver();

	//デバッグ
	void DebagDraw();
};