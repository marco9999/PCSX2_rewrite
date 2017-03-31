#include "stdafx.h"

#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"
#include "Common/Types/Registers/Register16_t.h"
#include "Common/Types/Registers/MIPS/PCRegister16_t.h"
#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Registers/Constant/ConstantFPRegister128_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister16_t.h"

#include "Resources/EE/VPU/VU/Types/VUCores_t.h"
#include "Resources/EE/VPU/VU/Types/VUCoreRegisters_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

VUCore_t::VUCore_t(const int vuCoreID) :
	mVUCoreID(vuCoreID),
	VF{ std::make_shared<ConstantFPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>() },
	VI{ std::make_shared<ConstantRegister16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(),
		std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>() },
	ACC(std::make_shared<FPRegister128_t>()),
	I(std::make_shared<FPRegister32_t>()),
	Q(std::make_shared<FPRegister32_t>()),
	R(std::make_shared<FPRegister32_t>()),
	P(std::make_shared<FPRegister32_t>()),
	Status(std::make_shared<VUCoreRegister_Status_t>()),
	MAC(std::make_shared<VUCoreRegister_MAC_t>(Status)),
	Clipping(std::make_shared<VUCoreRegister_Clipping_t>()),
	PC(std::make_shared<PCRegister16_t>()),
	CMSAR(std::make_shared<VUCoreRegister_CMSAR_t>()),
	MemPhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_32KB, Constants::SIZE_4KB, Constants::SIZE_16B)),
	MEMORY_Micro(nullptr),
	MEMORY_Mem(nullptr)
{
}

VUCore_VU0_t::VUCore_VU0_t(const std::shared_ptr<EECoreCOP0_t> & cop0) :
	VUCore_t(CORE_ID),
	COP0(cop0)
{
	MEMORY_Micro = std::make_shared<ByteMemory_t>(Constants::SIZE_4KB, "VU0 Micro Mem");
	MEMORY_Mem = std::make_shared<ByteMemory_t>(Constants::SIZE_4KB, "VU0 Main Mem");
}

bool VUCore_VU0_t::isCoprocessorUsable() const
{
	// Check that CU[bit 2] == 1 (ie: >0) in the status register.
	if ((COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::CU) & 0x4) > 0)
		return true;
	else
		return false;
}

VUCore_VU1_t::VUCore_VU1_t() :
	VUCore_t(CORE_ID)
{
	MEMORY_Micro = std::make_shared<ByteMemory_t>(Constants::SIZE_16KB, "VU1 Micro Mem");
	MEMORY_Mem = std::make_shared<ByteMemory_t>(Constants::SIZE_16KB, "VU1 Main Mem");
}