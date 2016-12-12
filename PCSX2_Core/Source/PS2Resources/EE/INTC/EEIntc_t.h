#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class ZeroMemory_t;
class EEIntcRegister_STAT_t;
class EEIntcRegister_MASK_t;

class EEIntc_t : public PS2ResourcesSubobject
{
public:
	explicit EEIntc_t(const PS2Resources_t *const PS2Resources);

	/*
	INTC memory mapped registers. See page 24 of EE Users Manual.
	*/
	std::shared_ptr<EEIntcRegister_STAT_t> REGISTER_STAT;
	std::shared_ptr<EEIntcRegister_MASK_t> REGISTER_MASK;
	std::shared_ptr<ZeroMemory_t>          MEMORY_f020;
};

