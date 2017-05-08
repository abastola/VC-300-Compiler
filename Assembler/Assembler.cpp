//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"


/**/
/*
Assembler::Assembler(int argc, char *argv[])
NAME
	Assembler::Assembler(int argc, char *argv[])
SYNOPSIS
	Assembler::Assembler(int argc, char *argv[])
	argc		-->			Number of Arguments
	argv		-->			Commandline Arguments

DESCRIPTION
	Constructor of Assembler Class
RETURNS
	VOID
AUTHOR
	Arjun Bastola
DATE
	3:08 PM 5/7/2017
*/
/**/


Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
	// Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler()
{
}
// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.

/**/
/*
void Assembler::PassI()
NAME
	Assembler::PassI() - Pass I of Instructions to Create Symbol Table
SYNOPSIS
	void Assembler::PassI()
DESCRIPTION
	Parses Instruction and adds them to Symbol Table
RETURNS
	VOID
AUTHOR
	Arjun Bastola
DATE
	3:08 PM 5/7/2017
	*/
/**/

void Assembler::PassI()
{
	int loc = 0;        // Tracks the location of the instructions to be generated.

	// Successively process each line of source code.
	for (; ; ) {

		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff)) {
			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}
		// If the instruction has a label, record it and its location in the
		// symbol table.
		if (m_inst.isLabel()) {
			// Check if the label is defined already
			int lookup_label;
			if (m_symtab.LookupSymbol(m_inst.GetLabel(), lookup_label)) {
				Errors::RecordError(m_inst.GetLabel() + ": Multiple Defination Error");
			}

			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}

/**/
/*
void Assembler::PassII()
NAME
	Assembler::PassII() - Pass II of Instructions; Translates to Assembler Code
SYNOPSIS
	void Assembler::PassII()
DESCRIPTION
	Translates Insyructions to Machine Level Code
RETURNS
	VOID
AUTHOR
	Arjun Bastola
DATE
	3:08 PM 5/7/2017
*/
/**/

void Assembler::PassII() {
	int loc = 0;        // Tracks the location of the instructions to be generated.

	//Go to Beginning of the file
	m_facc.rewind();

	//Location of each instruction
	int InstructionLocation_int = 0;

	//Print out Heading
	system("pause");
	cout << endl;
	cout << "Translation of Program:" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "Location\t" << "Contents\t"  << "Original Statement" << endl;

	//Pass each line parsed from Pass I
	do {
		string buff;
		if (!m_facc.GetNextLine(buff)) {

			//If no more lines, "END" is missing
			//Add this to Error
			string Error_Msg = "End Statement Missing";
			Errors::RecordError(Error_Msg);
			break;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		//Check for Valid Label
		//Must be 1-to chars and the first of which is a letter and the remaining may be letters and digits

		if (m_inst.GetLabel().length() > 10) {
			string Error_Msg = m_inst.GetLabel() + ": Label too Long";
			Errors::RecordError(Error_Msg);
		}
		else {
			char first_char = m_inst.GetLabel()[0];
			if (first_char >= '0' && first_char <= '9') {
				string Error_Msg = m_inst.GetLabel() + ": Label can't start with Number";
				Errors::RecordError(Error_Msg);
			}
		}

		//Check for Valid Opcode
		if (st == Instruction::ST_Invalid) {
			string Error_Msg = buff + ": Illegal Opcode";
			Errors::RecordError(Error_Msg);
		}

		//Check for End Statement
		//Done if it an End Statement
		if (st == Instruction::ST_End) {
			break;
		}

		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) {
			cout << "\t \t \t \t" << m_inst.GetInstruction() << endl;
			continue;
		}

		//Calculate Content Based on Opcodevalue
		value_int = 10000 * m_inst.GetOpCodeValue();

		//Check Assembly language
		if (st == Instruction::ST_AssemblerInstr) {
			if (m_inst.GetOpCode() == "DC") {
				value_int += m_inst.GetOprandValue();
			}
			if (m_inst.GetOpCode() != "END") {
				if (m_inst.GetOperand().empty()) {
					string Error_Msg = m_inst.GetOpCode() + ": Operand for Opcode Empty";
					Errors::RecordError(Error_Msg);
				}
				else if (!m_inst.IsNumeric()) {
					string Error_Msg = m_inst.GetOpCode() + ": No numeric value or Opcode";
					Errors::RecordError(Error_Msg);
				}
				if (m_inst.GetOpCode() != "ORG" && m_inst.GetLabel().empty()) {
					string Error_Msg = m_inst.GetOpCode() + ": No Label Provided";
					Errors::RecordError(Error_Msg);
				}
			}
		}
		else {
			//Check if Operand is Numeric
			//If yes, continue getting the value
			//If not, get Location in symbol table and add it to value

			if (m_inst.GetOperand().empty() && m_inst.GetOpCodeValue() != 13) {
				string Error_Msg = m_inst.GetOpCode() + ": Operand not Defined or Missing in Opcode";
				Errors::RecordError(Error_Msg);
			}
			else if (!m_inst.IsNumeric() && !m_inst.GetOperand().empty()) {
				int location_int = 0;
				if (!m_symtab.LookupSymbol(m_inst.GetOperand(), location_int)) {
					string Error_Msg = m_inst.GetOperand() + ": Symbol Not found";
					Errors::RecordError(Error_Msg);
					location_int = 9999;
				}
				value_int += location_int;
			}

		}

		if (m_emul.insertMemory(loc, value_int)) {

		}
		else {

		}

		cout  << setfill(' ') << setw(6) << loc << "\t \t";
		if (value_int != 0) {
			cout << setfill('0') << setw(6) << value_int << "\t \t";
		}
		else {

			cout <<  setw(6) << "\t \t";
		}
		cout <<  setw(10) << m_inst.GetInstruction() << endl;

		//Get next Instruction
		loc = m_inst.LocationNextInstruction(loc);

	} while (1);
}
/**/
/*
void Assembler::RunProgramInEmulator()
NAME
	Assembler::RunProgramInEmulator()
SYNOPSIS
	void Assembler::RunProgramInEmulator()
DESCRIPTION
	Runs Emulator for the Parsed Assembly Code
RETURNS
	VOID
AUTHOR
	Arjun Bastola
DATE
	3:08 PM 5/7/2017
*/
/**/

void Assembler::RunProgramInEmulator() {
	if (Errors::IsNoErrors) {
		m_emul.runProgram();
	}
	else {
		cout << "Error: Cannot Run Emulator" << endl;
		Errors::DisplayErrors();
	}
}


