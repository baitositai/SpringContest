#pragma once
#include "../framework.h"
#include "SceneBase.h"

class Player;
class ObjectManager;
class TimeCount;
class StageManager;
class PlayerUI;
class CountDown;
class GameBGM;
class Stage;
class SkyDome;
class HinderManager;

class GameScene : public SceneBase
{
public:

	//�Q�[�����̏��
	enum class STATE
	{
		NONE,
		START,	//�J�E���g�_�E��
		PLAY,	//�v���C
		RESULT,	//����
	};

	//�v���C���[�l��
	static constexpr int PLAYER_MAX = 2;

	//�v���C���[�̏����ʒu
	static constexpr VECTOR DEFAULT_PLAYER_POS = { 0,0,0 };

	//�v���C���[�̑���L�[
	static constexpr int RIGHT_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_D, KEY_INPUT_RIGHT };
	static constexpr int LEFT_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_A, KEY_INPUT_LEFT };
	static constexpr int JUMP_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_SPACE, KEY_INPUT_RETURN };
	static constexpr int TACKLE_MOVE_KEY[PLAYER_MAX] = { KEY_INPUT_W, KEY_INPUT_UP };

	//�J�����ʒu
	static constexpr VECTOR LOCAL_CAMERA_POS = { 0, 150, -200 };

	// �R���X�g���N�^
	GameScene(SceneManager& manager);

	// �f�X�g���N�^
	~GameScene() = default;

	void Load() override;
	void Init() override;
	void Update(InputManager& input) override;
	void Draw() override;
	void Release() override;

	//���ʕ`��
	void CommonDraw() override;

private:	

	//�v���C���[�l��
	int playNum_;

	//�J�n�J�E���g
	float strCnt_;

	//���
	STATE state_;

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void()>> stateChanges_;

	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void()> stateGameUpdate_;
	std::function<void()> stateGameDraw_;

	//�C���X�^���X����
	std::vector<std::shared_ptr<Player>> players_;
	std::vector<std::unique_ptr<ObjectManager>> objs_;
	std::unique_ptr<TimeCount> time_;
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<PlayerUI> uis_;
	std::unique_ptr<CountDown> cntDown_;
	std::unique_ptr<GameBGM> bgm_;
	std::unique_ptr<SkyDome> sky_;
	std::unique_ptr<HinderManager> hinder_;

	//�X�V�֐�
	void LoadingUpdate(InputManager& ins);	//�ǂݍ��ݒ�����
	void NormalUpdate(InputManager& ins);	//�Q�[��������
	
	//�`��֐� 
	void LoadingDraw();		//�ǂݍ��ݒ��`��
	void NormalDraw();		//�Q�[�����`��(��{�͂����ɏ����Ă�)

	//��ԑJ��
	void ChangeState(const STATE state);
	void ChangeStart();
	void ChangePlay();
	void ChangeResult();

	//�X�V�X�e�b�v
	void StartUpdate();	//��Ԃ�START�̎��ɍX�V���邱�Ƃ�����
	void PlayUpdate();	//PLAY�̎�(��{�͂����ɏ����Ă�)
	void ResultUpdate();//RESULT�̎�

	//�`��X�e�b�v
	void StartDraw();		//��Ԃ�START�̎��ɕ`�悷�邱�Ƃ�����
	void PlayDraw();		//PLAY�̎�
	void ResultDraw();		//RESULT�̎�

	//�Փ˔���
	void Collision();

	//�Q�[���I�[�o�[����
	void CheckGameOver();

	//������Ԃ̊m�F
	void CheckWinPlayer();

	//�f�o�b�O
	void DebagDraw();
};
