#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMapped_t.h"
#include "Common/Types/FIFOQueue32/FIFOQueue32_t.h"

/*
A transition layer, allowing a FIFO queue to be mapped into the PS2 physical memory space.
Only read/writeWord and Qword is allowed on non-zero storage indexes - all other combinations throw a runtime error.
*/
class MappedFIFOQueue32_t : public PhysicalMapped_t
{
public:
	explicit MappedFIFOQueue32_t(const u32 physicalAddress, const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	u8 readByte(const System_t context, size_t storageIndex) override;
	void writeByte(const System_t context, size_t storageIndex, u8 value) override;
	u16 readHword(const System_t context, size_t storageIndex) override;
	void writeHword(const System_t context, size_t storageIndex, u16 value) override;
	u32 readWord(const System_t context, size_t storageIndex) override;
	void writeWord(const System_t context, size_t storageIndex, u32 value) override;
	u64 readDword(const System_t context, size_t storageIndex) override;
	void writeDword(const System_t context, size_t storageIndex, u64 value) override;
	u128 readQword(const System_t context, size_t storageIndex) override;
	void writeQword(const System_t context, size_t storageIndex, u128 value) override;

	/*
	Gets the storage length, needed by the Physical MMU handler in order to map it.
	*/
	size_t getSize() override;

	/*
	Get the storage mnemonic, used for debug.
	*/
	const char * getMnemonic() const override;

private:
	/*
	The underlying FIFO queue this class maps to.
	*/
	std::shared_ptr<FIFOQueue32_t> mFIFOQueue32;
};