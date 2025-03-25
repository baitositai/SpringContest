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

	//‰æ‘œ“Ç‚İ‚İ
	int imgHinder_;
	int imgHinderGage_;

};

