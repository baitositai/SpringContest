#pragma once
#include "../framework.h"
#include "Common/Transform.h"
class ResourceManager;
class SceneManager;

class ObjectBase
{

public:

	// コンストラクタ
	ObjectBase(void);

	// デストラクタ
	~ObjectBase(void);

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);

	const Transform& GetTransform(void) const;

protected:

	// シングルトン参照
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// モデル制御の基本情報
	Transform transform_;
};