#include "FileUtils.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "tinyfiledialogs.h"

namespace Utils
{
	namespace File
	{
		std::string LoadToString(const std::string& filename)
		{
			try
			{
				std::ifstream inputFile(filename, std::ios::binary);
				if (!inputFile)
				{
					std::cerr << "Error: Failed to open file: " << filename << std::endl;
					return std::string();
				}
				return { std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>() };
			}
			catch (const std::exception& e)
			{
				std::cerr << "Exception: " << e.what() << std::endl;
				return std::string();
			}
		}

		void SaveFromString(const std::string& filename, std::string_view content)
		{
			std::ofstream outputStr(filename, std::ios::binary);
			if (!outputStr)
			{
				std::cerr << "Error: Failed to open file " << filename << " for writing.\n";
				return;
			}

			outputStr.write(content.data(), content.size());

			if (!outputStr) // Check if the write was successful
			{
				std::cerr << "Error: Failed to write to file " << filename << ".\n";
			}
		}

		std::string RemovePathFromFileName(const std::string& filePath)
		{
			return std::filesystem::path(filePath).filename().string();
		}

		std::string LoadDialog(const std::string& dialogText, const std::vector<const char*>& filtersArray)
		{
			try
			{
				auto filePath = tinyfd_openFileDialog("Select a file", "", (int)filtersArray.size(), filtersArray.data(), nullptr, false);
				
				return filePath;
			}
			catch (std::exception e)
			{
				return std::string();
			}
		}

		std::string SaveDialog(const std::string& dialogText, const std::string& currentFileName, const std::vector<const char*>& filtersArray)
		{
			auto filePath = tinyfd_saveFileDialog("Select a file", currentFileName.c_str(), (int)filtersArray.size(), filtersArray.data(), nullptr);
			
			if (filePath)
			{
				return filePath;
			}
			else
			{
				throw std::exception("Could not create a file path.");
			}
		}
	}
}

