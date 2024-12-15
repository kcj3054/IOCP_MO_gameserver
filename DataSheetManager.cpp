#include "DataSheetManager.h"
#include "ExecuteFunctionWithThreads.h"

bool DataSheetManager::LoadAllData(bool reload)
{
	//ExecuteFunctionWithThreads 여러 LoadGroup를 로딩한다 
	return ExecuteFunctionWithThreads(this, &DataSheetManager::LoadCharacterData,
		&DataSheetManager::LoadItemData,
		&DataSheetManager::LoadSkillData,
		&DataSheetManager::LoadMapData);
}

bool DataSheetManager::LoadCharacterData()
{
	return false;
}

bool DataSheetManager::LoadItemData()
{
	return false;
}

bool DataSheetManager::LoadSkillData()
{
	return false;
}

bool DataSheetManager::LoadMapData()
{
	return false;
}
