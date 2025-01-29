#pragma once
#include "../framework.h"
#include "SceneBase.h"

class GameScene : public SceneBase
{
public:

	// �R���X�g���N�^
	GameScene(SceneManager& manager);

	// �f�X�g���N�^
	~GameScene(void) = default;

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& input) override;
	void Draw(void) override;
	void Release(void) override;

private:	

	//Update�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//�`��֐� 
	void LoadingDraw(void);
	void NormalDraw(void);

	//�f�o�b�O
	void DebagDraw();
};

