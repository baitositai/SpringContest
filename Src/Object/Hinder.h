#pragma once
#include "../framework.h"

class Hinder
{
public:

	Hinder();
	~Hinder() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

private:

	//画像読み込み
	int imgHinder_;
	int imgHinderGage_;

};

