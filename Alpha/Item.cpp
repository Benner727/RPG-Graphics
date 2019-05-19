#include "Item.h"

#include <sstream>

Item::Item()
{

}

Item::Item(int _id, int _amount)
{
	mDefinitionLoader = DefinitionLoader::Instance();

	id = _id;
	amount = _amount;
	mItemTexture = Texture("Items/" + mDefinitionLoader->GetItemDefinition(_id)->getTexture());
	mItemTexture.Scale(Vector2(3.0f, 3.0f));

	mNoteTexture = Texture("Items/note.png");
	mNoteTexture.Scale(Vector2(3.0f, 3.0f));
}


Item::~Item()
{
	mDefinitionLoader = nullptr;
}

std::istream& operator >> (std::istream& in, Item& obj)
{
	in >> obj.id >> obj.amount;
	return in;
}

std::ostream& operator << (std::ostream& out, const Item& obj)
{
	out << obj.id << ' ' << obj.amount << std::endl;
	return out;
}

std::string Item::getName()
{
	return mDefinitionLoader->GetItemDefinition(id)->getName();
}

void Item::note()
{
	if (mDefinitionLoader->GetItemDefinition(id)->getNoteId() != -1)
	{
		if (!mDefinitionLoader->GetItemDefinition(id)->isNote())
			id = mDefinitionLoader->GetItemDefinition(id)->getNoteId();
	}
}

void Item::unNote()
{
	if (mDefinitionLoader->GetItemDefinition(id)->getNoteId() != -1)
	{
		if (mDefinitionLoader->GetItemDefinition(id)->isNote())
			id = mDefinitionLoader->GetItemDefinition(id)->getNoteId();
	}
}

bool Item::Intersects(Vector2 vec)
{
	if (mDefinitionLoader->GetItemDefinition(id)->isNote())
		return mNoteTexture.Intersects(vec);
	else
		return mItemTexture.Intersects(vec);
}

void Item::Render()
{
	if (mDefinitionLoader->GetItemDefinition(id)->isNote())
	{
		mNoteTexture.Pos(Pos());
		mNoteTexture.Render();
		mItemTexture.Scale(Vector2(2.0f, 2.0f));
	}
		
	mItemTexture.Pos(Pos());
	mItemTexture.Render();

	if (amount > 1)
	{
		CreateAmountText();
		
		for (int i = 0; i < mAmountText.size(); i++)
			mAmountText[i]->Render();
	}
}

void Item::CreateAmountText()
{
	for (int i = 0; i < mAmountText.size(); i++)
	{
		delete mAmountText[i];
		mAmountText[i] = nullptr;
	}

	mAmountText.clear();

	std::string str = std::to_string(amount);

	if (amount >= 10000000)
		str = std::to_string(amount / 1000000) + 'M';
	else if (amount >= 100000)
		str = std::to_string(amount / 1000) + 'K';

	int lastIndex = str.length() - 1;

	for (int i = 0; i <= lastIndex; i++)
	{
		mAmountText.push_back(new Texture(str.substr(i, 1), "Romulus.ttf", 16, { 255, 255, 255 }));
		mAmountText[i]->Pos(Vector2(mItemTexture.Pos().x + 24 - 8.0f * (lastIndex - i), mItemTexture.Pos().y - 24));
	}
}