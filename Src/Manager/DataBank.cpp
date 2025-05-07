#include "DataBank.h"

void DataBank::Init()
{
}

void DataBank::Input(const SceneManager::MODE& mode)
{
	systemInfo_.mode_ = mode;
}

void DataBank::Input(const bool& autoTackle)
{
	systemInfo_.autoTackle_ = autoTackle;
}

void DataBank::Input(const int& playerId)
{
	systemInfo_.playerId_ = playerId;
}

void DataBank::InputPlayNum(const int& playerNum)
{
	systemInfo_.playerNum_ = playerNum;
}

DataBank::DataBank()
{
	Init();
}
