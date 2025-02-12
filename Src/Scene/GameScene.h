#pragma once
#include "../framework.h"
#include "SceneBase.h"

class Player;
class ObjectManager;

class GameScene : public SceneBase
{
public:

	//�J�����ʒu
	static constexpr VECTOR LOCAL_CAMERA_POS = { 0, 150, -200 };

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

	//�C���X�^���X����
	std::shared_ptr<Player> player_;
	std::unique_ptr<ObjectManager> obj_;

	std::unique_ptr<ObjectBase> obj_;

	//Update�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//�`��֐� 
	void LoadingDraw(void);
	void NormalDraw(void);

	//�f�o�b�O
	void DebagDraw();
};

