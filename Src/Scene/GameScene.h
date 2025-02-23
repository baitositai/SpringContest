#pragma once
#include "../framework.h"
#include "SceneBase.h"

class Player;
class ObjectManager;
class TimeCount;

class GameScene : public SceneBase
{
public:

	//�Q�[���J�n�J�E���g�_�E��
	static constexpr float COUNTDOWN = 3.0f;

	//�Q�[�����̏��
	enum class STATE
	{
		START,	//�J�E���g�_�E��
		PLAY,	//�v���C
		REZALT,	//����
	};

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

	//�J�n�J�E���g
	float strCnt_;

	//���
	STATE state_;

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void(void)>> stateChanges_;

	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void(void)> stateGameUpdate_;
	std::function<void(void)> stateGameDraw_;

	//�C���X�^���X����
	std::shared_ptr<Player> player_;
	std::unique_ptr<ObjectManager> objs_;
	std::unique_ptr<TimeCount> time_;

	//�X�V�֐�
	void LoadingUpdate(InputManager& ins);	//�ǂݍ��ݒ�����
	void NormalUpdate(InputManager& ins);	//�Q�[��������
	
	//�`��֐� 
	void LoadingDraw(void);		//�ǂݍ��ݒ��`��
	void NormalDraw(void);		//�Q�[�����`��

	//��ԑJ��
	void ChangeState(STATE state);
	void ChangeStart(void);
	void ChangePlay(void);
	void ChangeRezalt(void);

	//�X�V�X�e�b�v
	void StartUpdate(void);
	void PlayUpdate(void);
	void RezaltUpdate(void);

	//�`��X�e�b�v
	void StartDraw();
	void PlayDraw();
	void RezaltDraw();

	//�Փ˔���
	void Collision();

	//�Q�[���I�[�o�[����
	void CheckGameOver();

	//�f�o�b�O
	void DebagDraw();
};