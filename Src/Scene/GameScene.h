#pragma once
#include "../framework.h"
#include "SceneBase.h"

class Player;
class ObjectManager;
class TimeCount;
class StageBase;

class GameScene : public SceneBase
{
public:

	//�Q�[�����̏��
	enum class STATE
	{
		START,	//�J�E���g�_�E��
		PLAY,	//�v���C
		REZALT,	//����
	};

	//�v���C���[�l��
	static constexpr int PLAYER_MAX = 2;

	//�Q�[���J�n�J�E���g�_�E��
	static constexpr float COUNTDOWN = 3.0f;

	//�v���C���[�̏����ʒu
	static constexpr VECTOR DEFAULT_PLAYER_POS = { 0,0,0 };

	//�v���C���[�̑���L�[
	static constexpr int RIGHT_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_D, KEY_INPUT_RIGHT };
	static constexpr int LEFT_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_A, KEY_INPUT_LEFT };
	static constexpr int JUMP_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_SPACE, KEY_INPUT_RETURN };
	static constexpr int TACKLE_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_Q, KEY_INPUT_RSHIFT };

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

	//�v���C���[�l��
	int playNum_;

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
	std::vector<std::shared_ptr<Player>> players_;
	std::vector<std::unique_ptr<ObjectManager>> objs_;
	std::unique_ptr<TimeCount> time_;

	//�X�e�[�W�֌W--------------------------------------
	//�X�e�[�W
	std::unique_ptr<StageBase> stage_;

	//�X�e�[�W�̓��I�z��
	std::vector<StageBase*> stages_;

	//�X�e�[�W�̏o���J�E���g
	int stageSpawnCounter_;

	//�X�e�[�W�̐�
	int stageSpawn_;
	//---------------------------------------------------

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
