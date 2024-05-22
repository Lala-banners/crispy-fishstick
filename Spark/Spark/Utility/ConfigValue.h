#pragma once

class ConfigValue final
{
public:
	ConfigValue() = delete;
	explicit ConfigValue(void* _value);

	~ConfigValue();

public:
	template<typename T>
	T Get();

private:
	void* m_value;

};

template <typename T>
T ConfigValue::Get()
{
	return *static_cast<T*>(m_value);
}