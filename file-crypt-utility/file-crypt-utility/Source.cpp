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
		_file_size = get_file_size(_file_path);
	}

	enum Operation
	{
		Encrypt,
		Decrypt
	};

	// Actual encryption/decryption method
	void run_operation(Operation operation)
	{
		const auto _base_path{ _file_path.parent_path() / _file_path.stem() };
		std::filesystem::path _output_file_path{ _base_path.string() + "2" + _file_path.extension().string() };
		std::ifstream _source_file{ _file_path, std::ios::binary };
		std::ofstream _output_file{ _output_file_path, std::ios::binary };
		constexpr int _buffer_size = 4096;
		std::array<char, _buffer_size> _file_buffer{};
		int _total_blocks{ _file_size / 4096 };

		try
		{
			if (_source_file.is_open() == false) 
				throw std::ios_base::failure("Failed to open source file");
			if (_output_file.is_open() == false) 
				throw std::ios_base::failure("Failed to open output file");

			_source_file.seekg(0);

			for (int i = 0; i < _total_blocks; i++)
			{
				_source_file.read(_file_buffer.data(), _file_buffer.size());


				_output_file.write(_file_buffer.data(), _file_buffer.size());
			}

			auto _remaining_size{ _file_size % _buffer_size };

			_source_file.read(_file_buffer.data(), _remaining_size);

			// XOR

			_output_file.write(_file_buffer.data(), _remaining_size);
		}
		catch (const std::ios_base::failure& e)
		{
			std::cout	<< "Caught an ios_base::failure.\n"
						<< "Explanatory string: " << e.what() << '\n'
						<< "Error code: " << e.code() << '\n';
		}
	}

	void xor_crypt()
	{
		//const char* key, int key_length, char* data, int data_length

		// if key_lenght < data_lenth
		// append key to itself until key_length =< data_length

		// get pointer of data
		// provider to buffer
		// get a key
		// overwrite existing data with encrypted data by reading a byte of data and XOR'ing with key
		

		const std::string _data = "This sentence is going to be used as example data.";
		//const std::string _data = "This sentence is going to be used as example data.";
		const int _data_length = _data.length();

		const std::string _key = "key";
		const int _key_length = _key.length();

		std::array<char, 50> _char_array{};
		std::array<char, 3> _key_array{};

		_data.copy(_char_array.data(), _data.length());
		_key.copy(_key_array.data(), _key.length());

		const int _block_size = 32; // 32 bytes

		std::array<char, 50> _converted_char_array{};

		int j = 0;
		for (int i = 0; i < _data_length; i++)
		{
			const char a = _char_array[i];
			const char b = _key_array[j];

			char x = a ^ b;

			_converted_char_array[i] = x;
			
			j++;
			if (j > 2)
			{
				j = 0;
			}
		}
	}

	void convert_string_to_char_key(std::string string_key)
	{

	}

private:
	std::filesystem::path _file_path;
	int _file_size;

	int get_file_size(std::filesystem::path path)
	{
		std::ifstream _source_file{ path, std::ios::binary };
		_source_file.seekg(0, std::ios_base::end);
		return _source_file.tellg();
	}

	// Method to encrypt a file
	void encrypt_file()
	{
		
	}

	// Method to decrypt a file
	void decrypt_file()
	{

	}
};

int main(int argc, char** argv)
{
	//std::int8_t _selected_option{ startup() };

	std::filesystem::path _path("C:\\Users\\yusuf\\Downloads\\red.jpg");

	file _newFile = file(_path);

	_newFile.run_operation(file::Encrypt);

	return 0;
}