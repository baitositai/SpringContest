#pragma once
#include "../framework.h"
#include "SceneBase.h"

class Player;
class ObjectManager;

class GameScene : public SceneBase
{
public:

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

	//インスタンス生成
	std::shared_ptr<Player> player_;
	std::unique_ptr<ObjectManager> obj_;

	std::unique_ptr<ObjectBase> obj_;

	//Update関数
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//描画関数 
	void LoadingDraw(void);
	void NormalDraw(void);

	//デバッグ
	void DebagDraw();
};

