#pragma once
#include "SceneBase.h"
#include "../framework.h"
#include "../Common/Vector2.h"
#include "../Manager/ResourceManager.h"

class TitlePlayer;
class TitleMesh;

class TitleScene : public SceneBase
{

public:

	enum class ROT_STATE
	{
		NONE,
		START,	//�J�n
		HALF,	//����]�ς�
	};

	//�^�C�g���t�H���g�T�C�Y
	static constexpr int MES_FONT_SIZE = 28;

	//����
	static constexpr int VOLUME = 70;

	//�V�[���J�ڕb��
	static constexpr int CHANGE_SCENE_SECOND = 180;

	//���S�ʒu
	static constexpr int LOGO_POS_X = 525;
	static constexpr int LOGO_POS_Y = 200;

	//���S�g�嗦
	static constexpr float LOGO_RATE = 0.5f;

	// �R���X�g���N�^
	TitleScene(SceneManager& manager);

	// �f�X�g���N�^
	~TitleScene(void) = default;

	void Load() override;
	void Init() override;
	void Update(InputManager& ins) override;
	void Draw() override;
	void Release() override;

	//���ʕ`��
	void CommonDraw() override;

private:	

	//�^�C�g���w�i
	int imgTitle_;

	//�^�C�g���w�i
	int imgTitleBackGround_;

	// ���b�Z�[�W�t�H���g
	int mesFont_;

	//�X�V�p�X�e�b�v
	float changeSceneStep_;

	// �X�V�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	// �`��֐�
	void LoadingDraw();
	void NormalDraw();

	//�v���C���[
	std::unique_ptr<TitlePlayer> titlePlayer_;

	//���b�V��
	std::unique_ptr<TitleMesh> titleMesh_;
};