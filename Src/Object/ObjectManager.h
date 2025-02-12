#pragma once
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

};

