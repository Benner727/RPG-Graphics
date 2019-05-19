#ifndef WEAPONDEFINITION_H
#define WEAPONDEFINITION_H

class WeaponDefinition
{
public:
	WeaponDefinition() {};

	WeaponDefinition(int _id, bool _twoHanded, int _speed)
	{
		id = _id;
		twoHanded = _twoHanded;
		speed = _speed;
	};

	~WeaponDefinition() {};

private:
	int id;
	bool twoHanded;
	int speed;

public:
	int getId() const { return id; }
	bool is2h() const { return twoHanded; }
	int getSpeed() const { return speed; }
};

#endif