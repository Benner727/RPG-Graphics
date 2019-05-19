#ifndef ITEMDEFINITION_H
#define ITEMDEFINITION_H

#include <string>

class ItemDefinition
{
public:
	ItemDefinition() {};

	ItemDefinition(std::string _name, int _id, bool _stackable, bool _note, int _noteId, int _alchemyPrice, int _generalPrice, std::string _texture)
	{
		name = _name;
		id = _id;
		stackable = _stackable;
		note = _note;
		noteId = _noteId;
		alchemyPrice = _alchemyPrice;
		generalPrice = _generalPrice;
		texture = _texture;
	};

	~ItemDefinition() {};

private:
	std::string name;
	int id;
	bool stackable,
		note;
	int noteId,
		alchemyPrice,
		generalPrice;
	std::string texture;

public:
	std::string getName() const { return name; }
	int getId() const { return id; }
	bool isStackable() const { return stackable; }
	bool isNote() const { return note; }
	int getNoteId() const { return noteId; }
	int getAlchemyPrice() const { return alchemyPrice; }
	int getGeneralPrice() const { return generalPrice; }
	std::string getTexture() const { return texture; }
};

#endif