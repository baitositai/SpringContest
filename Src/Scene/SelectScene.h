#pragma once
#include "../framework.h"
#include "SceneBase.h"

class SelectScene : public SceneBase
{
public:

	// コンストラクタ
	SelectScene(SceneManager& manager);

	// デストラクタ
	~SelectScene(void) = default;

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& input) override;
	void Draw(void) override;
	void Release(void) override;

	//書くことなし
	void CommonDraw() override;

private:

	// 更新関数
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//描画関数 
	void LoadingDraw(void);		//読み込み中描画
	void NormalDraw(void);		//ゲーム中描画

};

