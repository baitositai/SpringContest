#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"

class Player
{
public:

	Player();
	~Player();

	void Load();
	void Init();
	void Update();
	void Draw();

private:

	Transform trans_;

};

