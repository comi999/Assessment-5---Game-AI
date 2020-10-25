#pragma once
#include <typeinfo>
#include <map>
#include <set>

template <typename Key>
class AssetManager
{
public:
	AssetManager();
	~AssetManager();	

	template <typename Value>
	bool Insert(const Key& key, Value* values);

	template <typename Value>
	Value* Retrieve(const Key& key) const;

	template <typename Value>
	bool Remove(const Key& key);

	template <typename Value>
	bool Clear();

	bool Clear();

	template <typename Value>
	int Size();

	int Size();

	bool Contains(void* value);

	bool Empty();

private:
	typedef void(*Destructor)(void*);

	template<typename Value>
	static void Destroy(void* a_Address);

	int count;

	std::map<int, std::pair<std::pair<int, void*>, Destructor>>* map;
	std::set<void*>* set;
};

template <typename Key>
AssetManager<Key>::AssetManager()
{
	map = new std::map<int, std::pair<std::pair<int, void*>, Destructor>>();
	set = new std::set<void*>();

	count = 0;
}

template <typename Key>
AssetManager<Key>::~AssetManager()
{
	Clear();

	delete map;
	delete set;
}

template <typename Key>
template <typename Value>
bool AssetManager<Key>::Insert(const Key& key, Value* value)
{
	std::map<Key, Value*>* expectedMap;
	const std::type_info& typeInfo = typeid(expectedMap);
	int expectedHash = typeInfo.hash_code();

	auto typeMapPair = map->find(expectedHash);
	bool hasTypeMap = typeMapPair != map->end();

	if (hasTypeMap)
	{
		expectedMap = decltype(expectedMap)(typeMapPair->second.first.second);
		auto entryPair = expectedMap->find(key);
		bool hasKey = entryPair != expectedMap->end();

		if (!hasKey)
		{
			bool hasValue = !set->insert(value).second;
			if (!hasValue)
			{
				(*expectedMap)[key] = value;
				typeMapPair->second.first.first++;
				count++;
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
	{
		expectedMap = new std::map<Key, Value*>();
		(*expectedMap)[key] = value;

		(*map)[expectedHash];
		typeMapPair = map->find(expectedHash);
		typeMapPair->second.second = Destroy<Value>;
		typeMapPair->second.first.first = 1;
		typeMapPair->second.first.second = expectedMap;

		set->insert(value);
		count++;
		return true;
	}
}

template <typename Key>
template <typename Value>
Value* AssetManager<Key>::Retrieve(const Key& key) const
{
	std::map<Key, Value*>* expectedMap;
	const std::type_info& typeInfo = typeid(expectedMap);
	int expectedHash = typeInfo.hash_code();

	auto typeMapPair = map->find(expectedHash);
	bool hasTypeMap = typeMapPair != map->end();

	if (!hasTypeMap)
		return nullptr;

	expectedMap = decltype(expectedMap)(typeMapPair->second.first.second);

	auto expectedKeyPair = expectedMap->find(key);
	bool hasKeyPair = expectedKeyPair != expectedMap->end();

	if (!hasKeyPair)
		return nullptr;

	return expectedKeyPair->second;
}

template <typename Key>
template <typename Value>
bool AssetManager<Key>::Remove(const Key& key)
{
	std::map<Key, Value*>* expectedMap;
	const std::type_info& typeInfo = typeid(expectedMap);
	int expectedHash = typeInfo.hash_code();

	auto typeMapPair = map->find(expectedHash);
	bool hasTypeMap = typeMapPair != map->end();

	if (!hasTypeMap)
		return false;

	expectedMap = decltype(expectedMap)(typeMapPair->second.first.second);

	auto expectedKeyPair = expectedMap->find(key);
	bool hasKeyPair = expectedKeyPair != expectedMap->end();

	if (!hasKeyPair)
		return false;

	set->erase(expectedKeyPair->second);
	expectedMap->erase(expectedKeyPair);
	typeMapPair->second.first.first--;
	count--;
}

template <typename Key>
template <typename Value>
bool AssetManager<Key>::Clear()
{
	std::map<Key, Value*>* expectedMap;
	const std::type_info& typeInfo = typeid(expectedMap);
	int expectedHash = typeInfo.hash_code();

	auto typeMapPair = map->find(expectedHash);
	bool hasTypeMap = typeMapPair != map->end();

	if (!hasTypeMap)
		return false;

	Destructor destructor = typeMapPair->second.second;
	expectedMap = decltype(expectedMap)(typeMapPair->second.first.second);

	for (auto& mapEntry : *expectedMap)
	{
		set->erase(mapEntry.second);
		destructor(mapEntry.second);
	}

	delete expectedMap;
	count -= typeMapPair->second.first.first;
	map->erase(typeMapPair);
}

template <typename Key>
bool AssetManager<Key>::Clear()
{
	if (!count)
		return false;

	for (auto& typeMapPair : *map)
	{
		Destructor destructor = typeMapPair.second.second;
		auto typeMap = (std::map<Key, void*>*)(typeMapPair.second.first.second);

		for (auto& mapEntry : *typeMap)
			destructor(mapEntry.second);

		delete typeMap;
	}

	count = 0;

	map->clear();
	set->clear();

	return true;
}

template <typename Key>
template <typename Value>
int AssetManager<Key>::Size()
{
	std::map<Key, Value*>* expectedMap;
	const std::type_info& typeInfo = typeid(expectedMap);
	int expectedHash = typeInfo.hash_code();

	auto typeMapPair = map->find(expectedHash);
	bool hasTypeMap = typeMapPair != map->end();

	if (!hasTypeMap)
		return 0;

	return typeMapPair->second.first.first;
}

template <typename Key>
int AssetManager<Key>::Size()
{
	return count;
}

template <typename Key>
bool AssetManager<Key>::Contains(void* value)
{
	return set->find(value) != set->end();
}

template <typename Key>
bool AssetManager<Key>::Empty()
{
	return count == 0;
}

template <typename Key>
template <typename Value>
void AssetManager<Key>::Destroy(void* asset)
{
	delete (Value*)asset;
}