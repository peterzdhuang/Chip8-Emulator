#include <cstdint>
#include <fstream>
#include <chrono>
#include <random>
#include <string.h>

class Chip8 {
    public:
        uint8_t registers[16]{};
        uint8_t memory[4096]{};
        uint16_t index{};
        uint16_t pc{};
        uint16_t stack[16]{};
        uint8_t sp{};
        uint8_t delayTimer{};
        uint8_t soundTimer{};
        uint8_t keypad[16]{};
        uint32_t video[64 * 32]{};
        uint16_t opcode;

    const unsigned int START_ADDRESS = 0x200;
    const unsigned int FONTSET_SIZE = 80;
    const unsigned int FONTSET_START_ADDRESS = 0x50;
    std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

    void Chip8::LoadROM(char const* filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        
        if (file.is_open()) {
            std::streampos size = file.tellg();

            char* buffer = new char[size];

            file.seekg(0, std::ios::beg);
            file.read(buffer, size);
            file.close();

            for (long i = 0; i < size; i++) {
                memory[START_ADDRESS+i] = buffer[i];
            }
            
            delete[] buffer;
        }
    }

    Chip8::Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
        pc = START_ADDRESS;
        randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

        uint8_t fontset[FONTSET_SIZE] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
            memory[FONTSET_START_ADDRESS + i] = fontset[i];
        }

    }
    
    void Chip8::OP_00E0() {
        memset(video, 0, sizeof(video));
    }

    void Chip8::OP_00EE() {
        sp--;
        pc = stack[sp];
    }

    void Chip8::OP_1nnn(){
        uint16_t address = opcode & 0x0FFFu;
        pc = address;
    }

    void Chip8::OP_2nnn() {
        uint16_t address = opcode & 0x0FFFu; //0000 1111 1111 1111, 
        stack[sp] = pc;
        sp++;
        pc = address;
    }

    void Chip8::OP_3xkk() {
        uint8_t Vx = (opcode & 0x0FFFu) >> 8u;
        uint8_t byte = (opcode & 0x00FFu);

        if (registers[Vx] == byte) {
            pc += 2;
        }
    }

    void Chip8::OP_4xkk() {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        if (registers[Vx] != byte) {
            pc += 2;
        }
    }

    void Chip8::OP_5xy0() {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (registers[Vx] == registers[Vy])
        {
            pc += 2;
        }
    }

    void 

};

