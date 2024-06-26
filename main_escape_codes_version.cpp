/*
��� ��������� ��������� ANSI escape codes � Windows ������� ����� ������������ ��������� ����:

1. �������� ��������� ������ (Command Prompt).
2. ������� �������: reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
3. �������� � ����� �������� ��������� ������.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>


const std::string ANSI_BLUE		= "\033[34m";
const std::string ANSI_GREEN	= "\033[32m";
const std::string ANSI_YELLOW	= "\033[33m";
const std::string ANSI_RESET	= "\033[0m";


void loadSettingsFromFile(int& length_line, float& coffnt, std::string& charset)
{
	std::ifstream settingsFile("settings.cfg");

	if (settingsFile.is_open()) {
		settingsFile >> length_line >> coffnt;
		settingsFile.ignore();
		std::getline(settingsFile, charset);
		settingsFile.close();
	}
	else {
		length_line = 1;
		coffnt = 0.8;
		charset = "1234567890";
	}
}


void saveSettingsToFile(int length_line, float cofnt, const std::string& charset) {
	std::ofstream settingsFile("settings.cfg");

	if (settingsFile.is_open()) {
		settingsFile << length_line << std::endl;
		settingsFile << cofnt << std::endl;
		settingsFile << charset << std::endl;
		settingsFile.close();
	}
}


std::string generateRandomString(int length, const std::string& charset) {
	std::string randomString;
	size_t charsetSize = charset.size();

	for (int i = 0; i < length; ++i) {
		char randomChar = charset[std::rand() % charsetSize];
		randomString += randomChar;
	}

	return randomString;
}


/*
std::string getRandomColor()
{
	int colorCode = std::rand() % 3;

	switch (colorCode) {
	case 0:
		return ANSI_BLUE;
	case 1:
		return ANSI_GREEN;
	case 2:
		return ANSI_YELLOW;
	default:
		return ANSI_RESET;

	}
}
*/


static void clearConsole()
{
	std::cout << "\033[2J\033[1;1H";
}


int main()
{
	setlocale(LC_ALL, "");


	std::srand(std::time(nullptr));


	int length_line;
	float coffnt;
	std::string charset;


	loadSettingsFromFile(length_line, coffnt, charset);


	while (true) {
		clearConsole();

		std::cout << "��� ������ ������� \"exit\"" << std::endl;
		std::cout << "<" << length_line << "> " << "��������� ��������� ������: ";

		std::string line = generateRandomString(length_line, charset);

		for (char ch : line) {
			std::cout << /* getRandomColor() << */ ch;
		}
		

		std::cout << ANSI_RESET << std::endl;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((length_line * 1.5 + length_line) * 1000)));

		clearConsole();

		std::cout << "��� ������ ������� \"exit\"" << std::endl;
		std::cout << "<" << length_line << "> " << "������� ���������� ������ ";


		std::string userInput;
		std::cin >> userInput;

		if (userInput == "exit") {
			std::cout << "Exiting the program..." << std::endl;
			break;
		}


		if (userInput == line) {
			++length_line;
		}
		else if (length_line > 1) {
			--length_line;
		}


		saveSettingsToFile(length_line, coffnt, charset);
	}


	return 0;
}