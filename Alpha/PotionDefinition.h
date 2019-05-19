#ifndef POTIONDEFINITION_H
#define POTIONDEFINITION_H

#include <vector>

class PotionDefinition
{
public:
	struct SkillData
	{
		SkillData(int _skillId, int _add, double _modifier)
		{
			skillId = _skillId;
			add = _add;
			modifier = _modifier;
		}

		int skillId,
			add;
		double modifier;
	};

	PotionDefinition() {};

	PotionDefinition(int _id, int _replaceId, int _type, std::vector<SkillData> _skillData)
	{
		id = _id;
		replaceId = _replaceId;
		type = _type;
		skillData = _skillData;
	};

	~PotionDefinition() {};

private:
	int id,
		replaceId,
		type;
	std::vector<SkillData> skillData;

public:
	int getId() const { return id; }
	int getReplaceId() const { return replaceId; }
	int getType() const { return type; }
	std::vector<SkillData> getSkillData() const { return skillData; }
};

#endif