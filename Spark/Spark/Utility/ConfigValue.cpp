#include "ConfigValue.h"

ConfigValue::ConfigValue(void* _value)
	: m_value{ _value }
{
}

ConfigValue::~ConfigValue()
{
	// ReSharper disable once CppDeletingVoidPointer
	delete m_value;  // NOLINT(clang-diagnostic-delete-incomplete)
}