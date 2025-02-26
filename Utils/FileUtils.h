#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace Utils
{
	namespace File
	{
		std::string LoadToString(const std::string& filename);

		void SaveFromString(const std::string& filename, std::string_view content);

		std::string RemovePathFromFileName(const std::string& filePath);

		std::string LoadDialog(const std::string& dialogText = "Select a file", const std::vector<const char*>& filtersArray = {});
		
		std::string SaveDialog(const std::string& dialogText = "Select a file", const std::string& currentFileName = std::string(), const std::vector<const char*>& filtersArray = {});
	}
}

