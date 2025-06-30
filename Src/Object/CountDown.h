#pragma once

class CountDown
{
public:

	//ゲーム開始カウントダウン
	static constexpr float COUNTDOWN = 4.0f;

	//カウントダウン初期値
	static constexpr int SE_COUNT = 3;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CountDown();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CountDown() = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 解放
	/// </summary>
	void Release();

	/// <summary>
	/// 終了したら判定を返す
	/// </summary>
	/// <returns></returns>
	inline const bool IsStart() const { return isStart_; }

private:

	//画像
	int *imgNums_;

	//カウント
	float cnt_;

	//終了判定
	bool isStart_;

	//カウント
	int seCnt_;

	//効果音の再生処理
	void PlaySE();
	
};

