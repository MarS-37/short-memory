#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>


void loadSettingsFromFile(int& length_line, float& coffnt, std::string& charset)
{
	std::ifstream settingsFile("settings.txt");

	if (settingsFile.is_open()) {
		settingsFile >> length_line >> coffnt;
		settingsFile.ignore();
		std::getline(settingsFile, charset);
		settingsFile.close();
	}
	else {
		length_line = 1;
		coffnt = 1.5;
		charset = "1234567890";
	}
}


void saveSettingsToFile(int length_line, float cofnt, const std::string& charset) {
	std::ofstream settingsFile("settings.txt");

	if (settingsFile.is_open()) {
		settingsFile << length_line << std::endl;
		settingsFile << cofnt << std::endl;
		settingsFile << charset << std::endl;
		settingsFile.close();
	}
}


std::string generateRandomString(int length, const std::string& charset) {
	std::string randomString;
	int charsetSize = charset.size();

	for (int i = 0; i < length; ++i) {
		char randomChar = charset[std::rand() % charsetSize];
		randomString += randomChar;
	}

	return randomString;
}


static void clearConsole()
{
	std::cout << "\033[2J\033[1;1H";
}


int main()
{
	std::srand(std::time(nullptr));
	int length_line; 
	float coffnt;
	std::string charset;

	loadSettingsFromFile(length_line, coffnt, charset);

	while (true) {
		std::string line = generateRandomString(length_line, charset);
		std::cout << line << std::endl;
		

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((length_line * 1.5 + length_line) * 1000)));


		clearConsole();


		std::cout << "Enter the displayed string: ";


		std::string userInput;
		std::cin >> userInput;

		if (userInput == "exit") {
			std::cout << "Exiting the program..." << std::endl;
			break;
		}


		if (userInput == line) {
			++length_line;
		}
		else if(length_line > 1) {
			--length_line;
		}


		saveSettingsToFile(length_line, coffnt, charset);
	}


	return 0;
}