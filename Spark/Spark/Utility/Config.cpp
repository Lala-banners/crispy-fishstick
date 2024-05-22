#include "Config.h"

#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>
#include <pugixml/pugixml.hpp>
#include <raylib/raylib.h>

#include "StringUtils.h"
#include "Spark/Maths/Vec2.h"

using pugi::xml_parse_result;
using pugi::xml_node;
using pugi::xml_node;

using std::ifstream;
using std::vector;
using std::stringstream;

InvalidValueException::InvalidValueException(const string& _value)
	: value("Key not found: " + _value)
{
	
}

const char* InvalidValueException::what() const noexcept
{
	return value.c_str();
}

Config::Config()
	: m_doc{ new xml_document }
{
}

Config::~Config()
{
	for (auto& group : m_values | std::views::values)
	{
		for (const auto& val : group | std::views::values)
			delete val;
	}

	m_values.clear();
}

ConfigValue* Config::GetValue(const string& _category, const string& _id)
{
	if (m_values.contains(_category))
	{
		auto& set = m_values[_category];

		if (set.contains(_id))
			return set[_id];
	}

	return nullptr;
}

bool Config::TryGetValue(const string& _category, const string& _id, ConfigValue*& _value)
{
	if (HasValue(_category, _id))
	{
		_value = GetValue(_category, _id);
		return true;
	}

	return false;
}

bool Config::HasValue(const string& _category, const string& _id)
{
	if (m_values.contains(_category))
	{
		const auto& set = m_values[_category];
		return set.contains(_id);
	}

	return false;
}

EValueType Config::StringToType(const string& _type)
{
	if (_type == "int")
		return EValueType::Int;

	if (_type == "float")
		return EValueType::Float;

	if (_type == "bool")
		return EValueType::Bool;

	if (_type == "string")
		return EValueType::String;

	if (_type == "vector")
		return EValueType::Vector;

	if (_type == "color")
		return EValueType::Color;

	return EValueType::Invalid;
}

void Config::Clear()
{
	for (auto& group : m_values | std::views::values)
	{
		for (auto iter = group.begin(); iter != group.end(); ++iter)
			delete iter->second;
	}

	m_values.clear();
}

void Config::Load(const bool _initialise)
{
	if (_initialise && !Initialise())
		return;

	for (const xml_node& category : m_doc->child("Config").child("Categories").children("Category"))
	{
		string categoryTitle = category.attribute("title").as_string();

		for (const xml_node& value : category.children("Value"))
		{
			string valName = value.attribute("name").as_string();
			string valType = value.attribute("type").as_string();

			switch (StringToType(valType))
			{
			case EValueType::Int:
				m_values[categoryTitle][valName] = new ConfigValue(new int(value.attribute("value").as_int()));
				break;

			case EValueType::Float:
				m_values[categoryTitle][valName] = new ConfigValue(new float(value.attribute("value").as_float()));
				break;

			case EValueType::Bool:
				m_values[categoryTitle][valName] = new ConfigValue(new bool(value.attribute("value").as_bool()));
				break;

			case EValueType::String:
				m_values[categoryTitle][valName] = new ConfigValue(new string(value.attribute("value").as_string()));
				break;

			case EValueType::Vector:
				HandleVector(categoryTitle, valName, value.attribute("value").as_string());
				break;

			case EValueType::Color:
				HandleColor(categoryTitle, valName, value.attribute("value").as_string());
				break;

			case EValueType::Invalid:
				std::cout << "Type " << valType.c_str() << " was invalid! Make sure you mark the type as one of the following: int, float, bool, string, vector, color\n";
				break;
			}
		}
	}
}

void Config::HandleVector(const string& _category, const string& _id, const string& _value)
{
	auto converter = [](const string& _val) -> float
		{
			return std::stof(_val);
		};

	const vector<float> values = StringUtils::Split<float>(_value, ',', converter);

	m_values[_category][_id] = new ConfigValue(new Vec2{ values[0], values[1] });
}

void Config::HandleColor(const string& _category, const string& _id, const string& _value)
{
	auto converter = [](const string& _val) -> uint8_t
		{
			return static_cast<uint8_t>(std::stoi(_val));
		};

	const vector<uint8_t> values = StringUtils::Split<uint8_t>(_value, ',', converter);

	m_values[_category][_id] = new ConfigValue(new Color
		{
			values[0],
			values[1],
			values[2],
			values[3]
		});
}

bool Config::Initialise() const
{
	const xml_parse_result result = m_doc->load_file("./assets/config.xml");

	return result;
}