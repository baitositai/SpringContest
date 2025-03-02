#pragma once
#include "../../Common/IntVector3.h"

class StageBase
{
public:

	static constexpr float SIZE_Z = 7214.318;

	enum class STAGE_TYPE
	{
		STAGE,			//�ʏ�X�e�[�W
		STAGERIGHT,		//����E������
		STAGELEFT,		//���ꍶ������
		MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	StageBase(void);
	~StageBase(void);

	virtual void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetPos(IntVector3 pos);

protected:

	//�X�e�[�W
	int stage_[static_cast<int>(STAGE_TYPE::MAX)];

	//�X�e�[�W�^�C�v
	STAGE_TYPE type_;

	//���W
	IntVector3 pos_;

};
