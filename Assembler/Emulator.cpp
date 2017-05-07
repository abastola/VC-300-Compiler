#include "stdafx.h"
#include "Emulator.h"

bool emulator::insertMemory(int a_location, int a_contents) {
	if (a_location >= MEMSZ) {
		return false;
	}
	else {
		m_memory[a_location] = a_contents;
		return true;
	}
}

bool emulator::runProgram() {
	cout << "Results from emulating program: " << endl;
	cout << "------------------------------------------------------------" << endl;

	int OperandCode_int = 0;
	int UserInput_int = 0;
	int address_int = 0;
	bool isEnd=false;

	for (int i = 0; i < MEMSZ; i++) {
		if (m_memory[i] != 0) {
			OperandCode_int = m_memory[i] / MEMSZ;
			address_int = m_memory[i] % MEMSZ;

			switch (OperandCode_int) {

			case 1:
				// Add
				acceumulator += m_memory[address_int];
				break;

			case 2:
				// Substract
				acceumulator -= m_memory[address_int];
				break;

			case 3:
				// Multiply
				acceumulator *= m_memory[address_int];
				break;

			case 4:
				// Divide
				acceumulator = acceumulator / m_memory[address_int];
				break;

			case 5:
				// Load
				acceumulator = m_memory[address_int];
				break;

			case 6:
				// Store
				m_memory[address_int] = acceumulator;
				break;

			case 7:
				// Read
				cout << "Enter a Number: ";
				cin >> UserInput_int;
				m_memory[address_int] = UserInput_int;
				break;

			case 8:
				// Write
				cout << m_memory[address_int] << endl;
				break;

			case 9:
				// B
				i = address_int;
				break;

			case 10:
				// BM
				if (acceumulator < 0) {
					i = address_int - 1;
				}
				break;

			case 11:
				// BZ
				if (acceumulator == 0) {
					i = address_int - 1;
				}
				break;

			case 12:
				// BP
				if (acceumulator > 0) {
					i = address_int - 1;
				}
				break;

			case 13:
				// HALT
				isEnd=true;
				break;
			}
		}
		if (isEnd) {
			break;
		}
	}
	return false;
}