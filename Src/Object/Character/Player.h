#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"
#include "../Common/AnimationController.h"

class AnimationController;

class Player
{
public:

	//�ړ����x
	static constexpr float SPEED_MOVE = 5.0f;

	// �W�����v�֌W
	static constexpr float JUMP_HEIGHT = 100.0f;	//����
	static constexpr float JUMP_SPEED = 20.0f;		//�X�s�[�h
	static constexpr float RAD_PER_FRAME = 2 * DX_PI_F / 40; //1�t���[��������̃��W�A��

	// �W�����v��t����
	static constexpr float TIME_JUMP_IN = 0.5f;

	//�A�j���[�V�������x
	static constexpr float ANIM_SPEED = 40.0f;

	//�����̗�
	static constexpr int DEFAULT_LIFE = 3;

	//�����p���[
	static constexpr int DEFAULT_POWER = 4;

	//���a
	static constexpr float RADIUS = 30.0f;

	//�^�b�N������
	static constexpr float TACKLE_TIME = 1.5f;

	//�_���[�W����
	static constexpr float DAMAGE_TIME = 2.0f;

	//�^�b�N���G�t�F�N�g�̑��΍��W
	static constexpr VECTOR TACKLE_EFK_LOCAL_POS = { 0,100,100 };

	//�^�b�N���̃G�t�F�N�g�T�C�Y
	static constexpr float TACKLE_FEK_SIZE = 10.0f;

	//���
	enum class STATE
	{
		NONE,
		ALIVE,
		DEATH,
		WIN,
	};

	//�v���C���[�̐������
	enum class ALIVE_STATE
	{
		NONE,
		RUN,
		TACKLE,
		DAMAGE
	};

	//�A�j���[�V�������
	enum class ANIM_TYPE
	{
		NONE,
		IDLE,
		RUN,
		JUMP,
		TACKLE,
		DANCE,
		DEATH
	};

	//�����ŏ����ʒu���擾
	Player();
	~Player();

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

	//�̗͂�������
	void AddLife(const int &life);

	//�͂�������
	void AddPower(const int& pow);	
	
	//��Ԃ̕ύX
	void ChangeState(STATE state);

	//������Ԃ̕ύX
	void ChangeAliveState(const ALIVE_STATE & state);

	//����L�[�̐ݒ�
	void SetKey(
		const int& right, 
		const int& left, 
		const int& jump, 
		const int& tackle);

	//�̗͂�Ԃ�
	inline const int& GetLife() const { return life_; }

	//�͂�Ԃ�
	inline const int& GetPower() const { return pow_; }
	
	//�Փ˔���p���a��Ԃ�
	inline const float& GetRadius() const { return radius_; }

	//��Ԃ�Ԃ�
	inline const STATE& GetState() const { return state_; }

	//������Ԃ�Ԃ�
	inline const ALIVE_STATE& GetAliveState() const { return aliveState_; }

	//�g�����X�t�H�[����Ԃ�
	inline const Transform& GetTransform(void) const { return trans_; }

	//�f�o�b�O�`��
	void DebagDraw(); 

private:

	//����L�[
	struct Key
	{
		int right_;
		int left_;
		int jump_;
		int tackle_;
	};

	//���
	STATE state_;

	//�������
	ALIVE_STATE aliveState_;

	//�ړ����x
	float moveSpeed_;

	// �W�����v����
	bool isJump_;

	// �W�����v�̓��͎�t����
	float stepJump_;

	//�^�b�N���p���[
	int pow_;

	//�̗�
	int life_;

	//�Փ˔���p���a
	float radius_;

	//�^�b�N������
	float tackleTime_;

	//�_���[�W����
	float damageTime_;

	//�g�����X�t�H�[��
	Transform trans_;

	//�L�[
	Key key_;

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void(void)>> stateChanges_;
	std::map<ALIVE_STATE, std::function<void(void)>> aliveStateChanges_;

	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void(void)> stateUpdate_;
	std::function<void(void)> aliveStateUpdate_;

	// �A�j���[�V����
	std::unique_ptr<AnimationController> animationController_;

	// ��ԑJ��
	void ChangeStateNone(void);
	void ChangeStateAlive(void);
	void ChangeStateDeath(void);
	void ChangeStateWin(void);

	void ChanageAliveStateRun();
	void ChanageAliveStateTackle();
	void ChanageAliveStateDamage();

	// �X�V�X�e�b�v
	void UpdateNone(void);
	void UpdateAlive(void);
	void UpdateDeath(void);
	void UpdateWin(void);

	//�e�평���ݒ�
	void InitModel(void);
	void InitAnimation(void);

	//���쏈��
	void Process(void);

	//�W�����v
	void Jump(void);

	//������ԕʂ̍X�V����
	void Run();
	void Tackle();
	void Damage();
};

