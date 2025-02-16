#pragma once
#include "../Utility/StaticSingleton.h"

class ScrollManager : public StaticSingleton<ScrollManager>
{
public:

	//�ʏ�X�N���[���X�s�[�h
	static constexpr float DEFAULRT_SCROLL_SPEED = 5.0f;

	//����
	static constexpr float ACC_SPEED = 2.0f;

	//����
	static constexpr float DEC_SPEED = -2.0f;

	//�ړ�����
	static constexpr float MOVE_LIMIT_RIGHT = 250.0f;
	static constexpr float MOVE_LIMIT_LEFT = -250.0f;

	//�n��
	static constexpr float GROUND = 0.0f;

	//�X�N���[���J�n���C��
	static constexpr float SCROLL_START_LINE = 600.0f;

	//�X�N���[���I�����C��
	static constexpr float SCROLL_FINISH_LINE = -200.0f;

	ScrollManager();
	~ScrollManager() = default;

	void Init();
	void Update();

	//�X�N���[���X�s�[�h��Ԃ�
	float GetScrollSpeed()const;

	//�X�s�[�h�̕ύX
	void ChangeScrollSpeed(const float speed);

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(ScrollManager);

	//�X�N���[���X�s�[�h
	float scrollSpeed_;

};

