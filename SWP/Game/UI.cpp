#include "stdafx.h"
#include "UI.h"

void UI::Start(const std::string& name, const RECT& r)
{
	SetName(name);
	SetRect(r);
}

void UI::SetName(const std::string& name)
{
	_name.clear();
	_maxWidth = 0;

	std::vector<std::string> tokens;
	{
		char* result = strtok((char*)name.data(), "\n");
		while (result != NULL)
		{
			if (_maxWidth < strlen(result))
				_maxWidth = strlen(result);

			tokens.push_back(result);
			result = strtok(NULL, "\n");
		}
	}

	_name = tokens;
}
