#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <array>

std::int8_t startup()
{
	std::string _user_input{};
	std::int8_t _converted_input{};

	std::cout << "1: Encrypt a file" << std::endl;
	std::cout << "2: Decrypt a file" << std::endl;
	std::cout << "Please select option: ";

	std::getline(std::cin, _user_input);

	if (_user_input == "1")
	{
		std::cout << "You entered: " + _user_input << std::endl;
		_converted_input = std::stoi(_user_input);
		return _converted_input;
	}
	else if (_user_input == "2")
	{
		std::cout << "You entered: " + _user_input << std::endl;
		_converted_input = std::stoi(_user_input);
		return _converted_input;
	}
	else
	{
		std::cout << "Invalid input, please enter correct input." << std::endl;
		startup();
	}
}

class file
{
public:
	file(std::filesystem::path file_path)
	{
		_file_path = file_path;
	}

	// Method to encrypt a file
	void encrypt_file()
	{
		const auto _file_size{ get_file_size(_file_path) };
		std::ifstream _file_stream{ _file_path, std::ios::binary };
		const auto _base_path{ _file_path.parent_path() / _file_path.stem() };
		std::filesystem::path _new_path{ _base_path.string() + "2" + _file_path.extension().string()};
		std::ofstream _output_file{ _new_path, std::ios::binary };
		constexpr int _buffer_size = 4096;
		std::array<char, _buffer_size> _buffer{};
		std::uintmax_t _total_batches{ (_file_size / 4096) };

		if (_file_stream.is_open() == false && _output_file.is_open() == false)
		{
			std::cerr << "Failed to open file D:" << std::endl;
			return;
		}
		else 
		{
			_file_stream.seekg(0);

			for (int i = 0; i < _total_batches; i++)
			{
				_file_stream.read(_buffer.data(), _buffer.size());
				_output_file.write(_buffer.data(), _buffer.size());
			}

			auto _remaining_size{ _file_size % _buffer_size };

			_file_stream.read(_buffer.data(), _remaining_size);
			_output_file.write(_buffer.data(), _remaining_size);
		}
	}

	// Method to decrypt a file
	void decrypt_file()
	{

	}

private:
	std::filesystem::path _file_path;
	int64_t _current_character;
	uintmax_t _file_size;

	uintmax_t get_file_size(std::filesystem::path path)
	{
		return std::filesystem::file_size(path);
	}

	void read_file_section()
	{

	}
};

int main(int argc, char** argv)
{
	//std::int8_t _selected_option{ startup() };

	std::filesystem::path _path("C:\\Users\\yusuf\\Downloads\\asd.zip");

	file _newFile = file(_path);

	_newFile.encrypt_file();

	return 0;
}