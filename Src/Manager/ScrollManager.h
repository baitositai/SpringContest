#pragma once
#include "../Utility/StaticSingleton.h"

class ScrollManager : public StaticSingleton<ScrollManager>
{
public:

	//�ʏ�X�N���[���X�s�[�h
	static constexpr float DEFAULRT_SCROLL_SPEED = 10.0f;

	ScrollManager();
	~ScrollManager();

	void Init();
	void Update();
	void Release();

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(ScrollManager);

	//�X�N���[���X�s�[�h
	float scrollSpeed_;

};

