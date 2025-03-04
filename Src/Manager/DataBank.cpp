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

DataBank::DataBank()
{
	Init();
}
