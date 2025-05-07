#pragma once
#include "../../framework.h"
#include "../../Manager/SceneManager.h"
#include "Hinder.h"
#include "HinderObject.h"

class Hinder;
class HinderObject;

class HinderManager
{
public:

	//’Ç‰Á—Ê
	static constexpr int ADD_OBJS = 2;

	HinderManager();
	~HinderManager() = default;

	void Load();
	void Init();
	void Update();
	void Draw();

private:


	std::unique_ptr<Hinder> hinders_[SceneManager::PLAYER_MAX];
	std::unique_ptr<HinderObject> objs_[SceneManager::PLAYER_MAX];

	//–WŠQ‚ðŽó‚¯‚é‚©’²‚×‚é
	void CheckHinder();

};

