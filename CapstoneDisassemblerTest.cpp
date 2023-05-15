#include <iostream>

#include "CapstoneDisassembler.hpp"

int main()
{
	const auto example_code = reinterpret_cast<const uint8_t*>("\x55\x48\x8b\x05\xb8\x13\x00\x00");
	constexpr int address = 0x1ABC;

	for (const auto disassembled_instructions = disassemble(address, example_code, sizeof example_code);
	     const auto & disassembled_instruction : disassembled_instructions)
	{
		std::cout << disassembled_instruction.to_string() << std::endl;
	}

	const auto example_code_2 = reinterpret_cast<const uint8_t*>("\x55\x48\x8b\x05\xb8\x13\x00\x00\xCC\xCC\xCC\x01");
	for (const auto disassembled_instructions = disassemble(address, example_code_2);
		const auto & disassembled_instruction : disassembled_instructions)
	{
		std::cout << disassembled_instruction.to_string() << std::endl;
	}

	const auto example_code_3 = std::string(reinterpret_cast<const char*>(example_code), sizeof example_code);

	for (const auto disassembled_instructions = disassemble(address, example_code_3);
		const auto & disassembled_instruction : disassembled_instructions)
	{
		std::cout << disassembled_instruction.to_string() << std::endl;
	}
}