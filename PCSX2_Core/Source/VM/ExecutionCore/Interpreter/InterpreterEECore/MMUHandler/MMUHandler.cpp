#include "stdafx.h"

#include <cmath>

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/MMUHandler/MMUHandler.h"
#include "Common/Types/PS2Exception/PS2Exception_t.h"
#include "Common/PS2 Resources/EE/EECore/R5900/MMU/MMU_t.h"

using TLBEntryInformation = MMU_t::TLBEntryInformation;

MMUHandler::MMUHandler(const VMMain *const vmMain) : VMExecutionCoreComponent(vmMain)
{
}

u8 MMUHandler::readByteU(u32 PS2MemoryAddress) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::READ);
	return getVM()->getMMU()->readByteU(PS2PhysicalAddress);
}

void MMUHandler::writeByteU(u32 PS2MemoryAddress, u8 value) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::WRITE);
	getVM()->getMMU()->writeByteU(PS2PhysicalAddress, value);
}

s8 MMUHandler::readByteS(u32 PS2MemoryAddress) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::READ);
	return getVM()->getMMU()->readByteS(PS2PhysicalAddress);
}

void MMUHandler::writeByteS(u32 PS2MemoryAddress, s8 value) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::WRITE);
	getVM()->getMMU()->writeByteS(PS2PhysicalAddress, value);
}

u16 MMUHandler::readHwordU(u32 PS2MemoryAddress) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::READ);
	return getVM()->getMMU()->readHwordU(PS2PhysicalAddress);
}

void MMUHandler::writeHwordU(u32 PS2MemoryAddress, u16 value) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::WRITE);
	getVM()->getMMU()->writeHwordU(PS2PhysicalAddress, value);
}

s16 MMUHandler::readHwordS(u32 PS2MemoryAddress) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::READ);
	return getVM()->getMMU()->readHwordS(PS2PhysicalAddress);
}

void MMUHandler::writeHwordS(u32 PS2MemoryAddress, s16 value) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::WRITE);
	getVM()->getMMU()->writeHwordS(PS2PhysicalAddress, value);
}

u32 MMUHandler::readWordU(u32 PS2MemoryAddress) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::READ);
	return getVM()->getMMU()->readWordU(PS2PhysicalAddress);
}

void MMUHandler::writeWordU(u32 PS2MemoryAddress, u32 value) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::WRITE);
	getVM()->getMMU()->writeWordU(PS2PhysicalAddress, value);
}

s32 MMUHandler::readWordS(u32 PS2MemoryAddress) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::READ);
	return getVM()->getMMU()->readWordS(PS2PhysicalAddress);
}

void MMUHandler::writeWordS(u32 PS2MemoryAddress, s32 value) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::WRITE);
	getVM()->getMMU()->writeWordS(PS2PhysicalAddress, value);
}

u64 MMUHandler::readDwordU(u32 PS2MemoryAddress) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::READ);
	return getVM()->getMMU()->readDwordU(PS2PhysicalAddress);
}

void MMUHandler::writeDwordU(u32 PS2MemoryAddress, u64 value) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::WRITE);
	getVM()->getMMU()->writeDwordU(PS2PhysicalAddress, value);
}

s64 MMUHandler::readDwordS(u32 PS2MemoryAddress) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::READ);
	return getVM()->getMMU()->readDwordS(PS2PhysicalAddress);
}

void MMUHandler::writeDwordS(u32 PS2MemoryAddress, s64 value) const
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, AccessType::WRITE);
	getVM()->getMMU()->writeDwordS(PS2PhysicalAddress, value);
}

u32 MMUHandler::getPS2PhysicalAddress(const u32 & PS2VirtualAddress, const AccessType & accessType) const
{
	const u32 & PS2PhysicalAddress = getPS2PhysicalAddress_Stage1(PS2VirtualAddress, accessType);
#if defined(BUILD_DEBUG)
	char messsage[1000];
	sprintf_s(messsage, 1000, "EECore MMU: Returned address for PS2 VA = 0x%08lX to PS2 PA = 0x%08lX.", PS2VirtualAddress, PS2PhysicalAddress);
	logDebug(messsage);
#endif
	return PS2PhysicalAddress;
}

u32 MMUHandler::getPS2PhysicalAddress_Stage1(const u32 & PS2VirtualAddress, const AccessType & accessType) const
{
	// This process follows the information and diagram given on page 121 & 122 of the EE Core Users Manual. 
	// I am unsure if this is exactly what happens, as the information is a bit vague on how to obtain the page mask and ASID, 
	//  but I'm confident this is what it meant (I also dont see another way to do it).
	// Note: In the kernel context mode, for an VA in kseg0 and kseg1 a physical address is immediately returned, as they are both unmapped - no translation occurs.

	// BIG NOTE: where the lower bound of memory segments is 0x00000000, it has been omitted from the test statement (as it is implied through the use of u32).

	// Step 1 is to determine which CPU context we are in (user, supervisor or kernel).
	// User mode when KSU = 2, ERL = 0, EXL = 0 in the status register.
	if (getVM()->getResources()->EE->EECore->COP0->isOperatingUserMode())
	{
		// Operating in user mode.
		// First we check if the VA is within the context bounds.
		if (PS2VirtualAddress > PS2Constants::EE::EECore::MMU::VADDRESS_USER_UPPER_BOUND)
		{
			// Throw address error if not within bounds.
			if (accessType == READ) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD);
			else if (accessType == WRITE) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_ADDRESS_ERROR_STORE);
			else 
				throw std::runtime_error("MMUHandler: could not throw internal PS2Exception_t error (type = address error).");
		}

		return getPS2PhysicalAddress_Stage2(PS2VirtualAddress, accessType);
	}
	else if (getVM()->getResources()->EE->EECore->COP0->isOperatingSupervisorMode())
	{
		// Operating in supervisor mode.
		// First we check if the VA is within the context bounds.
		if ((PS2VirtualAddress > PS2Constants::EE::EECore::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_1 && PS2VirtualAddress < PS2Constants::EE::EECore::MMU::VADDRESS_SUPERVISOR_LOWER_BOUND_2) ||
			(PS2VirtualAddress > PS2Constants::EE::EECore::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_2))
		{
			// Throw address error if not within bounds.
			if (accessType == READ) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD);
			else if (accessType == WRITE) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_ADDRESS_ERROR_STORE);
			else 
				throw std::runtime_error("MMUHandler: could not throw internal PS2Exception_t error (type = address error).");
		}

		return getPS2PhysicalAddress_Stage2(PS2VirtualAddress, accessType);
	} 
	else if (getVM()->getResources()->EE->EECore->COP0->isOperatingKernelMode())
	{
		// Operating in kernel mode.
		// We do not need to check if the VA is valid - it is always valid over the full 4GB (U32) address space. However, kseg0 and kseg1 are not mapped, 
		//  and instead directly translate to physical addresses from 0x00000000 -> 0x1FFFFFFF (we need to emulate this). We also need to test for if
		//  Status.ERL == 1, in which case kuseg is unmapped. See EE Core Users Manual page 113 (especially notes).

		// Test for kseg0
		if (PS2VirtualAddress >= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_LOWER_BOUND_2 && PS2VirtualAddress <= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_UPPER_BOUND_2)
		{
			// We are in kseg0, so to get the physical address we just minus the kseg0 base address of 0x80000000.
			// We also do not test for the Config.K0 status, as we do not involve caches unless it is an explicit request.
			return (PS2VirtualAddress - PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_LOWER_BOUND_2);
		}

		// Test for kseg1
		if (PS2VirtualAddress >= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && PS2VirtualAddress <= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
		{
			// We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
			return (PS2VirtualAddress - PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
		}
		
		// Test for Status.ERL = 1 (indicating kuseg is unmapped). Note that the VA still has to be within the segment bounds for this to work.
		if (getVM()->getResources()->EE->EECore->COP0->Status->getRawFieldValue(RegisterStatus_t::Fields::ERL) == 1) {
			if (PS2VirtualAddress <= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_UPPER_BOUND_1)
			{
				// We are in kuseg unmapped region, so just return the VA.
				return PS2VirtualAddress;
			}
		}

		// Else in a mapped region - do normal translation.
		return getPS2PhysicalAddress_Stage2(PS2VirtualAddress, accessType);
	}
	else
	{
		// Throw runtime error as this should never happen.
		throw std::runtime_error("MMUHandler: could not determine context. Needs debugging!");
	}
}

u32 MMUHandler::getPS2PhysicalAddress_Stage2(const u32 & PS2VirtualAddress, const AccessType & accessType) const
{
	// Stage 2 is to search through the TLB to see if there is a VPN match. 
	// Check if its in the TLB and get the information.
	s32 index = getVM()->getResources()->EE->EECore->R5900->MMU->findTLBIndex(PS2VirtualAddress);
	if (index == -1)
	{
		// A match was not found, throw a TLB miss PS2 exception.
		if (accessType == READ) 
			throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD);
		else if (accessType == WRITE) 
			throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_REFILL_STORE);
		else 
			throw std::runtime_error("MMUHandler: could not throw internal PS2Exception_t error (type = tlb refill).");
	}
	TLBEntryInformation tlbEntry = getVM()->getResources()->EE->EECore->R5900->MMU->getTLBEntry(index);

	// Check the global bit, and check ASID if needed (against the ASID value in the EntryHi COP0 register).
	if (tlbEntry.mG == 0)
	{
		// Not a global page map, need to make sure ASID's are the same.
		if (getVM()->getResources()->EE->EECore->COP0->EntryHi->getRawFieldValue(RegisterEntryHi_t::Fields::ASID) != tlbEntry.mASID)
		{
			// Generate TLB refill exception.
			if (accessType == READ) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD);
			else if (accessType == WRITE) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_REFILL_STORE);
			else 
				throw std::runtime_error("MMUHandler: could not throw internal PS2Exception_t error (type = tlb refill).");
		}
	}

	// Move on to stage 3.
	return getPS2PhysicalAddress_Stage3(PS2VirtualAddress, accessType, tlbEntry);
}

u32 MMUHandler::getPS2PhysicalAddress_Stage3(const u32 & PS2VirtualAddress, const AccessType & accessType, const TLBEntryInformation & tlbEntry) const
{
	// Stage 3: Assess if the page is valid and it is marked dirty.
	// Need to check now before continuing if the VPN is for a even or odd page. This is done by checking the LSB of the VPN from the original address accessed.
	// Neat trick: +1 to the TLB mask to get the mask for the LSB of the VPN.
	if (PS2VirtualAddress & (tlbEntry.mMask + 1))
	{
		// Odd
		// Check if the entry is valid (V bit)
		if (!tlbEntry.mVOdd)
		{
			// Raise TLB invalid exception
			if (accessType == READ) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD);
			else if (accessType == WRITE) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_INVALID_STORE);
			else 
				throw std::runtime_error("MMUHandler: could not throw internal PS2Exception_t error (type = tlb invalid).");
		}	
		
		// Check if entry is allowed writes (dirty flag)
		if (!tlbEntry.mDOdd)
		{
			// Raise TLB modified exception if writing occurs.
			if (accessType == WRITE) throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_MODIFIED);
		}

		// Move on to stage 4 (odd)
		return getPS2PhysicalAddress_Stage4Odd(PS2VirtualAddress, accessType, tlbEntry);
	}
	else
	{
		// Even
		// Check if the entry is valid (V bit)
		if (!tlbEntry.mVEven)
		{
			// Raise TLB invalid exception
			if (accessType == READ) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD);
			else if (accessType == WRITE) 
				throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_INVALID_STORE);
			else 
				throw std::runtime_error("MMUHandler: could not throw internal PS2Exception_t error (type = tlb invalid).");
		}

		// Check if entry is allowed writes (dirty flag)
		if (!tlbEntry.mDEven)
		{
			// Raise TLB modified exception if writing occurs.
			if (accessType == WRITE) throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TLB_MODIFIED);
		}

		// Move on to stage 4 (odd)
		return getPS2PhysicalAddress_Stage4Even(PS2VirtualAddress, accessType, tlbEntry);
	}
}

u32 MMUHandler::getPS2PhysicalAddress_Stage4Odd(const u32 & PS2VirtualAddress, const AccessType & accessType, const TLBEntryInformation& tlbEntry) const
{
	// Check if accessing scratchpad
	if (tlbEntry.mS)
	{
		// TODO: implement accessing scratchpad. Idea on how to do this: map the reserved region 0x14000000 -> 0x1FBFFFFF to point to the SPRAM, using the VM MMU as this region will be unmapped anyway. The reserved region is 192 MB, plenty of space.
		throw std::runtime_error("MMUHandler: scratchpad access not yet implemented.");
	}

	// Or cache access?
	// Note: We actually dont need this in the emulator as the C flag only describes the cache method, not a location. The location is still refering to main memory.
	// See EE Core Users Manual page 126.
	/*
	if (tlbEntry.mCOdd > 0)
	{
	}
	*/

	// Else we are accessing main memory.
	// Combine PFN with offset using the TLB entry mask.
	u32 PFNBitPos = static_cast<u32>(log2(tlbEntry.mMask + 1));
	return ((tlbEntry.mPFNOdd << PFNBitPos) || (PS2VirtualAddress & tlbEntry.mMask));
}

u32 MMUHandler::getPS2PhysicalAddress_Stage4Even(const u32 & PS2VirtualAddress, const AccessType & accessType, const TLBEntryInformation& tlbEntry) const
{
	// Check if accessing scratchpad
	if (tlbEntry.mS)
	{
		// TODO: implement accessing scratchpad. Idea on how to do this: map the reserved region 0x14000000 -> 0x1FBFFFFF to point to the SPRAM, using the VM MMU as this region will be unmapped anyway. The reserved region is 192 MB, plenty of space.
		throw std::runtime_error("MMUHandler: scratchpad access not yet implemented.");
	}

	// Or cache access?
	// Note: We actually dont need this in the emulator as the C flag only describes the cache method, not a location. The location is still refering to main memory.
	// See EE Core Users Manual page 126.
	/*
	if (tlbEntry.mCOdd > 0)
	{
	}
	*/

	// Else we are accessing main memory.
	// Combine PFN with offset using the TLB entry mask.
	u32 PFNBitPos = static_cast<u32>(log2(tlbEntry.mMask + 1));
	return ((tlbEntry.mPFNEven << PFNBitPos) || (PS2VirtualAddress & tlbEntry.mMask));
}
