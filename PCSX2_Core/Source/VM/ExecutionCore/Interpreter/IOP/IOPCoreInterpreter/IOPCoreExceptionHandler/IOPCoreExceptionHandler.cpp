#include "stdafx.h"

#include <stdexcept>

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreExceptionHandler/IOPCoreExceptionHandler.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"
#include "Common/Tables/IOPCoreExceptionsTable/IOPCoreExceptionsTable.h"

IOPCoreExceptionHandler::IOPCoreExceptionHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain), 
	mIOPException(nullptr), 
	mExceptionProperties(nullptr)
{
}

void IOPCoreExceptionHandler::checkExceptionState()
{
	auto& Exceptions = getResources()->IOP->IOPCore->Exceptions;
	if (Exceptions->hasExceptionOccurred())
	{
		handleException(Exceptions->getException());
	}
}

void IOPCoreExceptionHandler::handleException(const IOPCoreException_t& PS2Exception)
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;
	auto& PC = getResources()->IOP->IOPCore->R3000->PC;

	// Set the PS2Exception pointer and get properties.
	mIOPException = &PS2Exception;
	mExceptionProperties = IOPCoreExceptionsTable::getExceptionInfo(PS2Exception.mExType);

#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;

	// Debug print exception type.
	logDebug("(%s, %d) IOPCoreExceptionHandler called! Type = %s", __FILENAME__, __LINE__, mExceptionProperties->mMnemonic);
#endif

	// Call the exception specific handler contained in the ExceptionProperties_t.
	(this->*EXCEPTION_HANDLERS[mExceptionProperties->mImplementationIndex])();

	// If its a reset exception, set PC to reset vector and return.
	if (mIOPException->mExType == ExType::EX_RESET)
	{
		PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
		return;
	}

	// Perform general exception handler code.
	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	COP0->Cause->setFieldValue(IOPCoreCOP0Register_Cause_t::Fields::ExcCode, mExceptionProperties->mExeCode);

	// Set EPC and Cause.BD fields, based on if we are in the branch delay slot.
	// Note that the EPC register should point to the instruction that caused the exception - so it is always set to at least PC - 4.
	if (getResources()->IOP->IOPCore->R3000->isInBranchDelaySlot())
	{
		// TODO: no idea if this code works, yet to encounter a branch delay exception.
		u32 pcValue = PC->getPCValue() - Constants::SIZE_MIPS_INSTRUCTION * 2;
		COP0->EPC->setFieldValue(COP0RegisterEPC_t::Fields::EPC, pcValue);
		COP0->Cause->setFieldValue(IOPCoreCOP0Register_Cause_t::Fields::BD, 1);
	}
	else
	{
		u32 pcValue = PC->getPCValue() - Constants::SIZE_MIPS_INSTRUCTION;
		COP0->EPC->setFieldValue(COP0RegisterEPC_t::Fields::EPC, pcValue);
		COP0->Cause->setFieldValue(IOPCoreCOP0Register_Cause_t::Fields::BD, 0);
	}

	// Select the vector to use (set vectorOffset).
	if (mIOPException->mExType == ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD || mIOPException->mExType == ExType::EX_TLB_REFILL_STORE)
		vectorOffset = PS2Constants::MIPS::Exceptions::Imp0::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
	else
		vectorOffset = PS2Constants::MIPS::Exceptions::Imp0::OADDRESS_EXCEPTION_VECTOR_V_COMMON;

	// Select vector base to use and set PC to use the specified vector.
	if (COP0->Status->getFieldValue(IOPCoreCOP0Register_Status_t::Fields::BEV) == 1)
		PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
	else
		PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
	
	// Push the exception state within the COP0.Status register.
	COP0->Status->pushExStack();
}

void IOPCoreExceptionHandler::EX_HANDLER_INTERRUPT()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_TLB_MODIFIED()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_TLB_REFILL_STORE()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_STORE()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void IOPCoreExceptionHandler::EX_HANDLER_BUS_ERROR_LOAD_STORE()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void IOPCoreExceptionHandler::EX_HANDLER_SYSTEMCALL()
{
	// No additional processing needed.
}

void IOPCoreExceptionHandler::EX_HANDLER_BREAK()
{
	// No additional processing needed.
}

void IOPCoreExceptionHandler::EX_HANDLER_RESERVED_INSTRUCTION()
{
	// No additional processing needed.
}

void IOPCoreExceptionHandler::EX_HANDLER_COPROCESSOR_UNUSABLE()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	COP0->Cause->setFieldValue(IOPCoreCOP0Register_Cause_t::Fields::CE, mIOPException->mCOPExceptionInfo.mCOPUnusable);
}

void IOPCoreExceptionHandler::EX_HANDLER_OVERFLOW()
{
	// No additional processing needed.
}

void IOPCoreExceptionHandler::EX_HANDLER_RESET()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	// Initalise all of the COP0 registers.
	COP0->initalise();

	COP0->Status->setFieldValue(IOPCoreCOP0Register_Status_t::Fields::SwC, 0);
	COP0->Status->setFieldValue(IOPCoreCOP0Register_Status_t::Fields::KUc, 0);
	COP0->Status->setFieldValue(IOPCoreCOP0Register_Status_t::Fields::IEc, 0);
	COP0->Status->setFieldValue(IOPCoreCOP0Register_Status_t::Fields::BEV, 1);
}