#pragma once
#include "Common/Transform.h"
class ResourceManager;
class SceneManager;

class ObjectBase
{

public:

	// �R���X�g���N�^
	ObjectBase(void);

	// �f�X�g���N�^
	virtual ~ObjectBase(void);

	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);

	const Transform& GetTransform(void) const;



protected:

	// �V���O���g���Q��
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// ���f������̊�{���
	Transform transform_;
};