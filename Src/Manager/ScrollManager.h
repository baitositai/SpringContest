#pragma once
#include "../Utility/StaticSingleton.h"

class ScrollManager : public StaticSingleton<ScrollManager>
{
public:

	//�ʏ�X�N���[���X�s�[�h
	static constexpr float DEFAULRT_SCROLL_SPEED = 10.0f;

	//����
	static constexpr float ACC_SPEED = 2.0f;

	//����
	static constexpr float DEC_SPEED = -2.0f;

	ScrollManager();
	~ScrollManager() = default;

	void Init();
	void Update();
	void Release();

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

