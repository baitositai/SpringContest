#pragma once
#include "../framework.h"

class ObjectBase;

class ObjectManager
{
public:

	ObjectManager();
	~ObjectManager() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

private:

	std::shared_ptr<ObjectBase> obj_;

};

