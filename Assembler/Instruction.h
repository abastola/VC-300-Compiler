//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

// The elements of an instruction.
class Instruction {

public:

	Instruction() {
		
	};
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.  Why is this inside the
	// class?
	enum InstructionType {
		ST_MachineLanguage, // A machine language instruction.
		ST_AssemblerInstr,  // Assembler Language instruction.
		ST_Comment,          // Comment or blank line
		ST_End,                    // end instruction.
		ST_Invalid
	};
	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff) {
		
		//Clear All Values
		m_Label.clear();
		m_OpCode.clear();
		m_Operand.clear();
		m_instruction.clear();
		m_OperandValue = -999999;
		m_NumOpCode = 0;
		m_IsNumericOperand = true;

		//Store a_buff (passed string to m_instruction)
		m_instruction = a_buff;

		//Constructs a istringstream object
		istringstream input_ss(a_buff);

		//To store extracted string from input_ss
		string extracted_str;

		//Extract first String from input_ss
		input_ss >> extracted_str;

		//Check to see if empty or comment line
		if (extracted_str.empty() || extracted_str.at(0) == ';') {
			return ST_Comment;
		}

		//Position of the label
		int position_int = 0;

		//Contains comment
		bool containsComment_bool=false;

		//Loop through the extracted_ss and store values
		while (!extracted_str.empty()) {

			//Check to see if there are comments
			int commentPosition_int = extracted_str.find(';');

			//Check is comment ';' is in first position 
			if (commentPosition_int == 0) {
				break;
			}

			//Check if comment ';' is in later position
			if (commentPosition_int > 0) {
				// Remove comment from extracted string
				extracted_str = extracted_str.substr(0, extracted_str.find(';'));

				containsComment_bool=true;
			}

			if (position_int == 0) {
				m_Label=extracted_str;
			}
			if (position_int == 1) {
				m_OpCode=extracted_str;
			}
			if (position_int == 2) {
				m_Operand = extracted_str;
			}

			//Increase the position of the new entity
			position_int++;

			//Clear the extracted string
			extracted_str.clear();

			//Get next extracted string
			input_ss >> extracted_str;

			if (containsComment_bool) {
				break;
			}

		}

		if (position_int == 1) {
			m_OpCode = m_Label;
			m_Label.clear();
		}

		//Check Validty of Labels
		else if (position_int == 2) {
			if (find(OperationCodes_arr.begin(), OperationCodes_arr.end(), m_OpCode) == OperationCodes_arr.end()) {
				if (find(AssemblerInstrcutions_arr.begin(), AssemblerInstrcutions_arr.end(), m_OpCode) == AssemblerInstrcutions_arr.end()) {
					m_Operand = m_OpCode;
					m_OpCode = m_Label;
					m_Label.clear();
				}
			}
		}

		// Convert OpCode to Uppercase
		for (int index = 0; index < m_OpCode.length(); index++) {
			m_OpCode[index] = toupper(m_OpCode[index]);
		}

		//Check if OpCode is Machine or Assembler
		if (find(OperationCodes_arr.begin(), OperationCodes_arr.end(), m_OpCode) != OperationCodes_arr.end()) {
			m_type = ST_MachineLanguage;
			m_NumOpCode = distance(OperationCodes_arr.begin(), find(OperationCodes_arr.begin(), OperationCodes_arr.end(), m_OpCode)) + 1;
		}
		
		else if (find(AssemblerInstrcutions_arr.begin(), AssemblerInstrcutions_arr.end(), m_OpCode) != AssemblerInstrcutions_arr.end()) {
			m_type = ST_AssemblerInstr;
		}
		
		// Check if OpCode is End
		else if (m_OpCode == "END") {
			m_type = ST_End;
		}

		// If nothing else, OpCode is Invalid
		else {
			m_type = ST_Invalid;
		}

		//Try if m_Operand is numeric value
		try {
			m_OperandValue = stoi(m_Operand);
		}
		catch (invalid_argument&) {
			m_IsNumericOperand = false;
		}

		cout << m_Label << " " << m_OpCode << " " << m_Operand << endl;
		// Compare it with the OpCode and return what type of instruction it is
		return m_type;
	};

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc) {
		// If DS or ORG, return a_lock plus Operand Value
		if (m_OpCode == "ORG" || m_OpCode == "DS"){
			return a_loc + m_OperandValue;
		}

		// Else returm a_loc plus one (next Instruction on source file)
		return (a_loc + 1);

	};

	// To access the label
	inline string &GetLabel() {

		return m_Label;
	};
	// To determine if a label is blank.
	inline bool isLabel() {

		return !m_Label.empty();
	};


private:


	// The elemements of a instruction
	string m_Label;            // The label.
	string m_OpCode;       // The symbolic op code.
	string m_Operand;      // The operand.

	// VIC ADD DUCK ; Quack Quack
	//first - get rid of comments - find_first_of
	//second - isstringstream
	//string a, b, c, d
	//iss >> a (vic) >> b (add) >> c (duck) >> d (nothing)
	// if(d) {someone messed up; we should only have d}
	// find opcode and what time of instruction it is


	string m_instruction;    // The original instruction.

	// Derived values.
	int m_NumOpCode;     // The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;   // The value of the operand if it is numeric.

	vector<string> OperationCodes_arr = { "ADD", "SUB", "MULT", "DIV", "LOAD", "STORE", "READ", "WRITE", "B", "BM", "BZ", "BP", "HALT" };
	vector<string> AssemblerInstrcutions_arr = {"DC", "DS", "ORG", "END" };
};


