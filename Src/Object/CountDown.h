#pragma once

class CountDown
{
public:

	//ゲーム開始カウントダウン
	static constexpr float COUNTDOWN = 4.0f;

	CountDown();
	~CountDown() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

	//終了したら判定を返す
	inline const bool IsStart() const { return isStart_; }

private:

	//画像
	int *imgNums_;

	//カウント
	float cnt_;

	//終了判定
	bool isStart_;
	
};

