#pragma once
class DataSheetManager
{
public:
	explicit DataSheetManager() = default;
	~DataSheetManager() = default;

public:
  bool LoadAllData(bool reload);


private:
	bool LoadCharacterData();

	bool LoadItemData();

	bool LoadSkillData();

	bool LoadMapData();
};

