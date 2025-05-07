#pragma once
#include <vector>
#include "../Utility/StaticSingleton.h"

class ScrollManager : public StaticSingleton<ScrollManager>
{
public:

	//�Œ�X�N���[���X�s�[�h
	static constexpr float DEFAULRT_SCROLL_SPEED = 5.0f;

	//�ō��X�N���[���X�s�[�h
	static constexpr float MAX_SCROLL_SPEED = 50.0f;

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
	static constexpr float SCROLL_START_LINE = 1200.0f;

	//�X�N���[���I�����C��
	static constexpr float SCROLL_FINISH_LINE = -500.0f;

	//���x�A�b�v����
	static constexpr int SPEED_UP_TIME = 30;

	ScrollManager();
	~ScrollManager() = default;

	//������
	void Init();

	//�X�N���[���X�s�[�h��Ԃ�
	inline const float GetScrollSpeed(const int playerId)const { return scrollSpeed_[playerId]; }

	//�X�s�[�h�̕ύX
	void ChangeScrollSpeed(const int playerId, const float speed);

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(ScrollManager);

	//�X�N���[���X�s�[�h
	std::vector<float> scrollSpeed_;

	//���x�A�b�v�p�X�e�b�v
	float step_;

};

