#pragma once

#include <vector>
#include <string>

using std::string;
using std::vector;
using std::istream;
using std::stringstream;

class StringUtils
{
public:
	static void RemoveAll(string& _string, const string& _toRemove);
	static void ReplaceAll(string& _string, const string& _toReplace, const string& _replacement);

	template<typename T>
	static vector<T> Split(const string& _string, char _deliminator, T(*_converter)(const string&));

};

template <typename T>
vector<T> StringUtils::Split(const string& _string, char _deliminator, T(* _converter)(const string&))
{
	vector<T> values;

	string s;
	for(const char c : _string)
	{
		if(c != _deliminator)
		{
			s += c;
		}
		else
		{
			// We have found a separator, so convert the type
			values.emplace_back(_converter(s));
			s.clear();
		}
	}

	if(!s.empty())
	{
		values.emplace_back(_converter(s));
		s.clear();
	}

	return values;
}