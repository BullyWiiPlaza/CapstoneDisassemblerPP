#pragma once

#include <vector>
#include <capstone/capstone.h>
#include <string>

class disassembled_instruction_t
{
	public:
		cs_insn instruction;

		[[nodiscard]] std::string to_string() const;
};

/**
 * \brief Disassembles a code buffer to assembly instructions.
 * \param address The address where disassembling should start
 * \param code The buffer pointing to the code to disassemble
 * \param code_size The length of the code buffer. If 0, the code will look for the next 0xCC byte to determine code size.
 * \return The vector of disassembled instructions
 */
[[nodiscard]] std::vector<disassembled_instruction_t> disassemble(uint64_t address, const uint8_t* code, size_t code_size = 0);

/**
 * \brief See the description of the other overload.
 */
[[nodiscard]] std::vector<disassembled_instruction_t> disassemble(uint64_t address, const std::string &code);