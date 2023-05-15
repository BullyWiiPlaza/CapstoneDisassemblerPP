#include "CapstoneDisassembler.hpp"

#include <iomanip>
#include <stdexcept>
#include <sstream>

constexpr auto interrupt_cc = 0xCC;

std::vector<disassembled_instruction_t> disassemble(const uint64_t address, const uint8_t* code, size_t code_size)
{
	if (code_size == 0)
	{
		// Try to find the code size automatically
		for (size_t byte_index = 0; byte_index < INT_MAX; byte_index++)
		{
			if (code[byte_index] == interrupt_cc
				&& code[byte_index + 1] == interrupt_cc
				&& code[byte_index + 2] == interrupt_cc)
			{
				code_size = byte_index;
				break;
			}
		}
	}

	std::vector<disassembled_instruction_t> disassembled_instructions;

	csh handle;
	if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
	{
		return disassembled_instructions;
	}

	cs_insn* instructions = nullptr;
	if (const auto instruction_count = cs_disasm(handle, code, code_size, address, 0, &instructions);
		instruction_count > 0)
	{
		for (size_t instruction_index = 0; instruction_index < instruction_count; instruction_index++)
		{
			const auto instruction = instructions[instruction_index];
			disassembled_instructions.push_back({ instruction });
		}

		cs_free(instructions, instruction_count);
	}
	else
	{
		throw std::runtime_error("Failed to disassemble code");
	}

	cs_close(&handle);

	return disassembled_instructions;
}

std::vector<disassembled_instruction_t> disassemble(const uint64_t address, const std::string& code)
{
	return disassemble(address, reinterpret_cast<const uint8_t*>(code.data()), code.size());
}

std::string to_hexadecimal_string(const uint8_t* data, const int length)
{
	std::stringstream stream;
	stream << std::hex;
	stream << std::uppercase;

	for (auto length_index = 0; length_index < length; length_index++)
	{
		stream << std::setw(2) << std::setfill('0') << static_cast<int>(data[length_index]);

		if (length_index != length -1)
		{
			stream << " ";
		}
	}

	return stream.str();
}

std::ostream& operator <<(std::stringstream& stream, const disassembled_instruction_t& disassembled_instruction)
{
	return stream << "0x" << std::hex << std::uppercase << disassembled_instruction.instruction.address
		<< ": " << to_hexadecimal_string(disassembled_instruction.instruction.bytes, disassembled_instruction.instruction.size)
		<< "\t" << disassembled_instruction.instruction.mnemonic
		<< " " << disassembled_instruction.instruction.op_str;
}

std::string disassembled_instruction_t::to_string() const
{
	std::stringstream stream;
	stream << *this;
	return stream.str();
}