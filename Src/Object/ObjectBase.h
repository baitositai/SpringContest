#pragma once
#include "../framework.h"
#include "Common/Transform.h"
class ResourceManager;
class SceneManager;

class ObjectBase
{

public:

	// �R���X�g���N�^
	ObjectBase(void);

	// �f�X�g���N�^
	~ObjectBase(void);

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);

	const Transform& GetTransform(void) const;

protected:

	// �V���O���g���Q��
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// ���f������̊�{���
	Transform transform_;
};