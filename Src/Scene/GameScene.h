#pragma once
#include "../framework.h"
#include "SceneBase.h"

class GameScene : public SceneBase
{
public:

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

	//Update関数
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//描画関数 
	void LoadingDraw(void);
	void NormalDraw(void);

	//デバッグ
	void DebagDraw();
};

