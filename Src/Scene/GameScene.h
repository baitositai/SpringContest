#pragma once
#include "../framework.h"
#include "SceneBase.h"

class Player;
class ObjectManager;
class TimeCount;
class StageManager;
class PlayerUI;
class CountDown;
class GameBGM;

class GameScene : public SceneBase
{
public:

	//ゲーム中の状態
	enum class STATE
	{
		NONE,
		START,	//カウントダウン
		PLAY,	//プレイ
		REZALT,	//結果
	};

	//プレイヤー人数
	static constexpr int PLAYER_MAX = 2;

	//プレイヤーの初期位置
	static constexpr VECTOR DEFAULT_PLAYER_POS = { 0,0,0 };

	//プレイヤーの操作キー
	static constexpr int RIGHT_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_D, KEY_INPUT_RIGHT };
	static constexpr int LEFT_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_A, KEY_INPUT_LEFT };
	static constexpr int JUMP_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_SPACE, KEY_INPUT_RETURN };
	static constexpr int TACKLE_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_W, KEY_INPUT_UP };

	//カメラ位置
	static constexpr VECTOR LOCAL_CAMERA_POS = { 0, 150, -200 };

	// コンストラクタ
	GameScene(SceneManager& manager);

	// デストラクタ
	~GameScene(void);

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& input) override;
	void Draw(void) override;
	void Release(void) override;

	//共通描画
	void CommonDraw() override;

private:	

	//プレイヤー人数
	int playNum_;

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
	std::vector<std::shared_ptr<Player>> players_;
	std::vector<std::unique_ptr<ObjectManager>> objs_;
	std::unique_ptr<TimeCount> time_;
	std::unique_ptr<StageManager> stage_;
	std::unique_ptr<PlayerUI> uis_;
	std::unique_ptr<CountDown> cntDown_;
	std::unique_ptr<GameBGM> bgm_;

	//更新関数
	void LoadingUpdate(InputManager& ins);	//読み込み中処理
	void NormalUpdate(InputManager& ins);	//ゲーム中処理
	
	//描画関数 
	void LoadingDraw(void);		//読み込み中描画
	void NormalDraw(void);		//ゲーム中描画(基本はここに書いてね)

	//状態遷移
	void ChangeState(STATE state);
	void ChangeStart(void);
	void ChangePlay(void);
	void ChangeRezalt(void);

	//更新ステップ
	void StartUpdate(void);	//状態がSTARTの時に更新することを書く
	void PlayUpdate(void);	//PLAYの時(基本はここに書いてね)
	void RezaltUpdate(void);//REZALTの時

	//描画ステップ
	void StartDraw();	//状態がSTARTの時に描画することを書く
	void PlayDraw();	//PLAYの時
	void RezaltDraw();	//REZALTの時

	//衝突判定
	void Collision();

	//ゲームオーバー判定
	void CheckGameOver();

	//勝利状態の確認
	void CheckWinPlayer();

	//デバッグ
	void DebagDraw();
};
