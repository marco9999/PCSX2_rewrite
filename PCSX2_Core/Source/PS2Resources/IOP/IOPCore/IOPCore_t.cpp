#include "stdafx.h"

#include <memory>

#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "Common/Types/Memory/DebugMemory_t.h"


IOPCore_t::IOPCore_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	R3000(std::make_shared<IOPCoreR3000_t>(getRootResources())),
	COP0(std::make_shared<IOPCoreCOP0_t>(getRootResources())),
	Exceptions(std::make_shared<IOPCoreExceptions_t>(getRootResources())),
	ScratchpadMemory(std::make_shared<DebugMemory_t>(PS2Constants::IOP::IOPCore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY, "IOP Core Scratchpad Memory"))
{
}
