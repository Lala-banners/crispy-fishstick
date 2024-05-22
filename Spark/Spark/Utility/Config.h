#pragma once

#include "ConfigValue.h"

#include <functional>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

using std::is_same;
using std::map;
using std::string;
using std::vector;

namespace pugi
{
	class xml_document;
}

using pugi::xml_document;

struct InvalidValueException final : std::exception
{
public:
	string value;

public:
	explicit InvalidValueException(const string& _value);

public:
	const char* what() const noexcept override;

};

enum class EValueType : int8_t
{
	Invalid = -1,
	Int,
	Float,
	Bool,
	String,
	Vector,
	Color
};

class Config
{
	friend class Application;

public:
	Config();
	~Config();

	Config(const Config&) = delete;
	Config(Config&&) = delete;

public:
	ConfigValue* GetValue(const string& _category, const string& _id);
	bool TryGetValue(const string& _category, const string& _id, ConfigValue*& _value);
	bool HasValue(const string& _category, const string& _id);

	template<typename T>
	T GetValue(const string& _category, const string& _id);
	template<typename T>
	bool TryGetValue(const string& _category, const string& _id, T& _value);

public:
	Config& operator=(const Config&) = delete;
	Config& operator=(Config&&) = delete;

private:
	xml_document* m_doc;

	map<string, map<string, ConfigValue*>> m_values;

private:
	static EValueType StringToType(const string& _type);

private:
	bool Initialise() const;
	void Clear();
	void Load(bool _initialise = true);

	void HandleVector(const string& _category, const string& _id, const string& _value);
	void HandleColor(const string& _category, const string& _id, const string& _value);

};

template <typename VAL>
VAL Config::GetValue(const string& _category, const string& _id)
{
	if (ConfigValue* value = GetValue(_category, _id))
		return value->Get<VAL>();

	return VAL();
}

template <typename VAL>
bool Config::TryGetValue(const string& _category, const string& _id, VAL& _value)
{
	if (HasValue(_category, _id))
	{
		_value = GetValue<VAL>(_category, _id);
		return true;
	}

	return false;
}