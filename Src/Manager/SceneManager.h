#pragma once
#include "../framework.h"
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Common/Vector2.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "Camera.h"

class SceneBase;
class InputManager;
class Fader;
class Camera;

class SceneManager : public StaticSingleton<SceneManager>
{

public:

	//FPS�l
	static constexpr float DEFAULT_FPS = 60.0f;

	//�d��
	static constexpr float GRAVITY = 9.81f;

	//�f���^�^�C��
	static constexpr float DELTA_TIME = 1.0f / 60.0f;

	//�ő�v���C�l��
	static constexpr int PLAYER_MAX = 2;

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		MOVIE,
		SELECT,
		GAME
	};

	//�l���Ǘ�
	enum class MODE
	{
		NONE,
		MARASON,
		VS,
	};
	
	void Init(void);
	void Init3D(void);

	/// <summary>
	/// �擪�́iUpdate���Ă΂��j�V�[����؂�ւ���
	/// </summary>
	/// <param name="scene">�؂�ւ���̃V�[��</param>
	void CreateScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// ���ׂẴV�[����؂�ւ���
	/// </summary>
	/// <param name="scene">�؂�ւ���̃V�[��</param>
	void ChangeAllScene(std::shared_ptr<SceneBase> scene);

	void Update(InputManager& ins);
	void Draw(void);

	// ���\�[�X�̔j��
	void Destroy(void);

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID();

	// �f���^�^�C���̎擾
	float GetDeltaTime() const;

	// �o�ߎ��Ԃ̎擾
	const float& GetTotalTime() const { return totalTime_; }

	// ���C���X�N���[���̎擾
	const int& GetMainScreen() const { return mainScreen_; }

	// �J�����̎擾
	std::vector<std::shared_ptr<Camera>> GetCameras() const;

	//�t�F�[�h�C���J�n
	void StartFadeIn();

	//�t�F�[�h�J���[�̎w��
	void SetFadeColor(unsigned int color);

	//�`��X�N���[���̃Z�b�g
	void SetDrawingScreen(const int screenID);

	//�`��X�N���[���̃J�E���g��Ԃ�
	inline const int GetScreenCount()const { return screenCnt_; }

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(SceneManager);

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// �t�F�[�h
	std::unique_ptr<Fader> fader_;

	// �J����
	std::vector<std::shared_ptr<Camera>> cameras_;

	// ���ݎ��s���̃V�[��
	std::list<std::shared_ptr<SceneBase>> scenes_;

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	//�o�ߎ���
	float totalTime_;

	//���C���X�N���[��
	int mainScreen_;
	int halfScreen_[PLAYER_MAX];

	//�X�N���[�����W
	Vector2 screenPos_;

	//�X�N���[���U��
	float amplitude_;

	//�t���[��
	int frame_;

	//�X�N���[���J�E���g
	int screenCnt_;

	//�`��p
	std::function<void(void)> drawFunc_;
	
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager();
	// �f�X�g���N�^�����l
	~SceneManager() = default;

	// �f���^�^�C�������Z�b�g����
	void ResetDeltaTime();

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

	// �t�F�[�h
	void Fade();

	// �ʏ�̕`��
	void NormalDraw();

	// VS�p�̕`��
	void VSPlayDraw();

};