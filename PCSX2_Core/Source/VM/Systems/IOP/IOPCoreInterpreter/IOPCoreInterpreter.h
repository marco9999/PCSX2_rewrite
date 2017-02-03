#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"

#include "VM/Types/VMSystem_t.h"

#include "Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

class VM;
class IOPCore_t;
class PhysicalMMU_t;
struct MIPSInstructionInfo_t;

/*
The IOP Interpreter. This is similar to a PS1 system - as such you can find resources on the internet for the PS1.
The clock speed of the IOP is roughly 1/8th that of the EE Core (~36 MHz, increased from the original PSX clock speed of ~33.8 MHz).

No official documentation, but there is resources available on the internet documenting the R3000 and other parts.
*/
class IOPCoreInterpreter : public VMSystem_t
{
public:
	explicit IOPCoreInterpreter(VM * vmMain);
	virtual ~IOPCoreInterpreter();

	/*
	Initalisation.
	*/
	void initalise() override;

	/*
	This is the "main loop" function called by the base interpreter component, and sub-functions it calls.
	*/
	double executeStep(const ClockSource_t & clockSource, const double & ticksAvailable) override;

private:

	//////////////////////////
	// Common Functionality //
	//////////////////////////

	/*
	Resources.
	*/
	std::shared_ptr<IOPCore_t> mIOPCore;
	std::shared_ptr<PhysicalMMU_t> mPhysicalMMU;

#if defined(BUILD_DEBUG)
	// Debug loop counter 
	u64 DEBUG_LOOP_COUNTER = 0;
#endif

	///////////////////////////////
	// Instruction Functionality //
	///////////////////////////////

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	It is also used while an instruction is being performed.
	*/
	MIPSInstruction_t mInstruction;
	const MIPSInstructionInfo_t * mInstructionInfo;

	/*
	Helper functions to check for: 
	 - The usability conditions of COP0.
	 - No over or underflow will occur for signed 32 bit integers.
	Returns a bool indicating if the instruction should return early because of unavailablity.
	Return early from instruction = true, proceed with instruction = false.
	They will automatically set the exception state as well.
	*/
	bool handleCOP0Usable();
	bool handleOverOrUnderflow32(const s32 & x, const s32 & y);

	// IOP Instruction funtionality.

	/*
	Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	If the BUILD_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	*/
	void INSTRUCTION_UNKNOWN();

	/*
	Computational (ALU) Instructions. See IOPInterpreter_ALU.cpp for implementations (31 instructions total).
	*/
	void ADD();
	void ADDI();
	void ADDIU();
	void ADDU(); 
	void SUB();
	void SUBU();
	void DIV();
	void DIVU();
	void MULT();
	void MULTU();
	void SLL();
	void SLLV();
	void SRA();
	void SRAV();
	void SRL();
	void SRLV();
	void AND();
	void ANDI();
	void NOR();
	void OR();
	void ORI();
	void XOR();
	void XORI();
	void SLT();
	void SLTI();
	void SLTIU();
	void SLTU();

	/*
	Load and Store from Memory Instructions. See IOPInterpreter_LOAD_STORE_MEM.cpp for implementations (14 instructions total).
	*/
	void LB();
	void LBU();
	void LH();
	void LHU();
	void LUI();
	void LW();
	void LWL();
	void LWR();
	void SB();
	void SH();
	void SW();
	void SWL();
	void SWR();


	/*
	Special Data Transfer Instructions. See IOPInterpreter_SPECIAL_TRANSFER.cpp for implementations (26 instructions total).
	*/
	void MFC0();
	void MTC0();
	void MFHI();
	void MFLO();
	void MTHI();
	void MTLO();

	/*
	(Conditional) Branch and Jump Instructions. See IOPInterpreter_BRANCH_JUMP.cpp for implementations (26 instructions total).
	*/
	void BEQ();
	void BGEZ();
	void BGEZAL();
	void BGTZ();
	void BLEZ();
	void BLTZ();
	void BLTZAL();
	void BNE();
	void J();
	void JR();
	void JAL();
	void JALR();

	/*
	Others Instructions. See IOPInterpreter_OTHERS.cpp for implementations (9 instructions total).
	*/
	void BREAK();
	void SYSCALL();
	void TLBP();
	void TLBR();
	void TLBWI();
	void TLBWR();

	/*
	TODO: sort through.
	*/
	void LWC2();
	void SWC2();
	void CFC0();
	void CTC0();
	void RFE();
	void RTPS();
	void NCLIP();
	void OP();
	void DPCS();
	void INTPL();
	void MVMVA();
	void NCDS();
	void CDP();
	void NCDT();
	void NCCS();
	void CC();
	void NCS();
	void NCT();
	void SQR();
	void DCPL();
	void DPCT();
	void AVSZ3();
	void AVSZ4();
	void RTPT();
	void GPF();
	void GPL();
	void MFC2();
	void CFC2();
	void MTC2();
	void CTC2();

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index.
	See IOPCoreInstructionTable and "IOP Instruction Implementation Register.xlsm" for more details.
	*/
	void(IOPCoreInterpreter::* IOP_INSTRUCTION_TABLE[Constants::IOP::IOPCore::NUMBER_IOP_INSTRUCTIONS])() =
	{
		&IOPCoreInterpreter::INSTRUCTION_UNKNOWN,
		&IOPCoreInterpreter::J,
		&IOPCoreInterpreter::JAL,
		&IOPCoreInterpreter::BEQ,
		&IOPCoreInterpreter::BNE,
		&IOPCoreInterpreter::BLEZ,
		&IOPCoreInterpreter::BGTZ,
		&IOPCoreInterpreter::ADDI,
		&IOPCoreInterpreter::ADDIU,
		&IOPCoreInterpreter::SLTI,
		&IOPCoreInterpreter::SLTIU,
		&IOPCoreInterpreter::ANDI,
		&IOPCoreInterpreter::ORI,
		&IOPCoreInterpreter::XORI,
		&IOPCoreInterpreter::LUI,
		&IOPCoreInterpreter::LB,
		&IOPCoreInterpreter::LH,
		&IOPCoreInterpreter::LWL,
		&IOPCoreInterpreter::LW,
		&IOPCoreInterpreter::LBU,
		&IOPCoreInterpreter::LHU,
		&IOPCoreInterpreter::LWR,
		&IOPCoreInterpreter::SB,
		&IOPCoreInterpreter::SH,
		&IOPCoreInterpreter::SWL,
		&IOPCoreInterpreter::SW,
		&IOPCoreInterpreter::SWR,
		&IOPCoreInterpreter::LWC2,
		&IOPCoreInterpreter::SWC2,
		&IOPCoreInterpreter::SLL,
		&IOPCoreInterpreter::SRL,
		&IOPCoreInterpreter::SRA,
		&IOPCoreInterpreter::SLLV,
		&IOPCoreInterpreter::SRLV,
		&IOPCoreInterpreter::SRAV,
		&IOPCoreInterpreter::JR,
		&IOPCoreInterpreter::JALR,
		&IOPCoreInterpreter::SYSCALL,
		&IOPCoreInterpreter::BREAK,
		&IOPCoreInterpreter::MFHI,
		&IOPCoreInterpreter::MTHI,
		&IOPCoreInterpreter::MFLO,
		&IOPCoreInterpreter::MTLO,
		&IOPCoreInterpreter::MULT,
		&IOPCoreInterpreter::MULTU,
		&IOPCoreInterpreter::DIV,
		&IOPCoreInterpreter::DIVU,
		&IOPCoreInterpreter::ADD,
		&IOPCoreInterpreter::ADDU,
		&IOPCoreInterpreter::SUB,
		&IOPCoreInterpreter::SUBU,
		&IOPCoreInterpreter::AND,
		&IOPCoreInterpreter::OR,
		&IOPCoreInterpreter::XOR,
		&IOPCoreInterpreter::NOR,
		&IOPCoreInterpreter::SLT,
		&IOPCoreInterpreter::SLTU,
		&IOPCoreInterpreter::BLTZ,
		&IOPCoreInterpreter::BGEZ,
		&IOPCoreInterpreter::BLTZAL,
		&IOPCoreInterpreter::BGEZAL,
		&IOPCoreInterpreter::MFC0,
		&IOPCoreInterpreter::CFC0,
		&IOPCoreInterpreter::MTC0,
		&IOPCoreInterpreter::CTC0,
		&IOPCoreInterpreter::RFE,
		&IOPCoreInterpreter::RTPS,
		&IOPCoreInterpreter::NCLIP,
		&IOPCoreInterpreter::OP,
		&IOPCoreInterpreter::DPCS,
		&IOPCoreInterpreter::INTPL,
		&IOPCoreInterpreter::MVMVA,
		&IOPCoreInterpreter::NCDS,
		&IOPCoreInterpreter::CDP,
		&IOPCoreInterpreter::NCDT,
		&IOPCoreInterpreter::NCCS,
		&IOPCoreInterpreter::CC,
		&IOPCoreInterpreter::NCS,
		&IOPCoreInterpreter::NCT,
		&IOPCoreInterpreter::SQR,
		&IOPCoreInterpreter::DCPL,
		&IOPCoreInterpreter::DPCT,
		&IOPCoreInterpreter::AVSZ3,
		&IOPCoreInterpreter::AVSZ4,
		&IOPCoreInterpreter::RTPT,
		&IOPCoreInterpreter::GPF,
		&IOPCoreInterpreter::GPL,
		&IOPCoreInterpreter::MFC2,
		&IOPCoreInterpreter::CFC2,
		&IOPCoreInterpreter::MTC2,
		&IOPCoreInterpreter::CTC2,
	};

	/////////////////////////////
	// Exception Functionality //
	/////////////////////////////

	/*
	Handles a given exception by running the general exception handler based on the exception properties defined.
	*/
	void handleException(const IOPCoreException_t & exception);

	/*
	Checks if any of the interrupt lines have an IRQ pending, and raises an interrupt exception.
	*/
	void handleInterruptCheck();

#if defined(BUILD_DEBUG)
	// Debug for counting the number of exceptions handled.
	u64 DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

	///////////////////////
	// MMU Functionality //
	///////////////////////

	/*
	Internal types used within/to access MMU.
	*/
	enum MMUAccess_t { READ, WRITE };

	/*
	Performs a lookup from the given virtual address and access type.
	Returns if an error occured, indicating if the instruction that called should return early (error = true, no error = false).
	The physical address calculated is stored in physicalAddress.

	The IOP Core has no TLB - all virtual addresses are directly converted to physical addresses based on kernel segments.
	Currently if the CPU is not in a kernel context or an MMU error occurs, a runtime_error exception will be thrown.
	TODO: investigate into user mode. I think the original PSX had no TLB...
	*/
	bool getPhysicalAddress(const u32 & virtualAddress, const MMUAccess_t & access, u32 & physicalAddress);
};

