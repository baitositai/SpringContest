#pragma once
#include "../../framework.h"
#include "ObjectBase.h"

class ObjectBase;

class ObjectManager
{
public:

	//スクロールの間隔秒数
	static constexpr float INTERVEL_SECOND_MIN = 1.0f;
	static constexpr float INTERVEL_SECOND_MAX = 2.0f;

	//各種オブジェクト生成数
	static constexpr int ENEMY_CREATE_CNT = 4;
	static constexpr int GIMIC_CREATE_CNT = 2;
	static constexpr int LIFE_CREATE_CNT = 1;
	static constexpr int POW_CREATE_CNT = 1;

	ObjectManager();
	~ObjectManager() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

	//オブジェクトを返す
	const std::vector<std::unique_ptr<ObjectBase>>& GetObjects() const;

private:

	//スクロール開始用ステップ
	float step_;

	//オブジェクト
	std::vector<std::unique_ptr<ObjectBase>> objs_;

	//スクロールの開始
	void ScrollStart();

	//次回のスクロール開始秒数
	float NextStartSecond();

};

