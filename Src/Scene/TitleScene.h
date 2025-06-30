#pragma once
#include "SceneBase.h"
#include "../framework.h"
#include "../Common/Vector2.h"
#include "../Manager/ResourceManager.h"

class TitlePlayer;
class TitleMesh;
class TitleStage;
class SkyDome;

class TitleScene : public SceneBase
{

public:

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

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager"></param>�V�[���Ǘ��N���X
	TitleScene(SceneManager& manager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name=""></param>
	~TitleScene(void) = default;

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	void Load() override;

	/// <summary>
	/// ������
	/// </summary>
	void Init() override;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="ins"></param>���͊Ǘ��N���X
	void Update(InputManager& ins) override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ���
	/// </summary>
	void Release() override;

	/// <summary>
	/// ���ʕ`��
	/// </summary>
	void CommonDraw() override;

private:	

	//�^�C�g���w�i
	int imgTitle_;

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

	//�X�e�[�W
	std::unique_ptr<TitleStage> stage_;

	//�X�J�C�h�[��
	std::unique_ptr<SkyDome> sky_;
};