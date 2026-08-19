#include <cstdint>
#include <iostream>
#include <array>
#include <vector>

class CPU
{
	public:
		// load the chosen program into memory
		void load_program(const std::vector<std::uint8_t>& program)
		{
			for(std::size_t i = 0; i < program.size(); ++i)
			{
				memory[i] = program[i];
			}
			return;
		}

		// step through the currently loaded program
		void step()
		{
			// if the CPU is halted, stop stepping
			if(halted == true)
				return;
			
			// fetch the next opcode
			std::uint8_t opcode = fetch();
			
			// use a switch statement to execute based on the currently loaded instruction
			switch(opcode)
			{
				// HALT
				case 0xFF:
					halted = true;
					break;
				// LOAD accumulator
				case 0x01:
					accumulator = fetch();
					break;
				// ADD immediate
				case 0x02:
					accumulator += fetch();
					break;
				// STORE accumulator
				case 0x03:
					memory[fetch()] = accumulator;
					break;
				// default case for bad naughty opcodes
				default:
					std::cout << "Unknown opcode: " << static_cast<int>(opcode) << "\n";
					halted = true;
					break;
				
			}
			return;
		}

		// run loop - acts like a clock driving the CPU
		void run()
		{
			while(halted == false)
			{
				step();
			}
		}


	private:
		// various simulated registers and RAM
		std::uint8_t accumulator = 0;
		std::uint8_t program_counter = 0;
		bool halted = false;
		// we are representing memory as an array of 8-bit vectors (8 bit registers if they were physically real)
		std::array<std::uint8_t, 256> memory{};

		// fetch the next instruction from our program
		std::uint8_t  fetch()
		{
			return memory[program_counter++];
		}
};



int main()
{
	// instantiate the toy CPU
	CPU toy_cpu;

	// example program
	std::vector<std::uint8_t> example_program = 
	{
		// LDA (load accumulator) is 0x01. 0x2 is the value to load into the accumulator 
		0x01, 0x2,
		// ADD immediate (add the following value to the accumulator)
		0x02, 0x03,
		// STORE the accumulator's current value in the following memory address
		0x03, 0xF0,
		// intentional nonsense opcode to test bad opcode handling
		0x69,
		// HALT
		0xFF,
	};

	// load the program into memory
	toy_cpu.load_program(example_program);

	// run the loaded program
	toy_cpu.run();

	return 0;
}
