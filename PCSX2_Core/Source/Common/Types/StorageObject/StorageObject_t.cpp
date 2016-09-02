#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/StorageObject/StorageObject_t.h"


StorageObject_t::StorageObject_t(const size_t & size, const std::string mnemonic) :
	mStorageSize(size),
	mStorage(new u8[mStorageSize]),
	mMnemonic(mnemonic)
{
	// Initalise storage to 0.
	memset(mStorage, 0, mStorageSize);

#if defined(BUILD_DEBUG)
	// Log the storage details if enabled.
	char message[1000];
	sprintf_s(message, 1000, "%s allocated at 0x%p (size = 0x%08zX).", mMnemonic.c_str(), mStorage, mStorageSize);
	logDebug(message);
#endif
}

StorageObject_t::~StorageObject_t()
{
}

u8 StorageObject_t::readByteU(u32 storageIndex)
{
	// Get client storage address.
	u8 * clientMemoryAddress = reinterpret_cast<u8*>(&mStorage[storageIndex]);

	// Read the value.
	return *clientMemoryAddress;
}

void StorageObject_t::writeByteU(u32 storageIndex, u8 value)
{
	// Get client storage address.
	u8 * clientMemoryAddress = reinterpret_cast<u8*>(&mStorage[storageIndex]);

	// Write the value.
	*clientMemoryAddress = value;
}

s8 StorageObject_t::readByteS(u32 storageIndex)
{
	// Get client storage address.
	s8 * clientMemoryAddress = reinterpret_cast<s8*>(&mStorage[storageIndex]);

	// Read the value.
	return *clientMemoryAddress;
}

void StorageObject_t::writeByteS(u32 storageIndex, s8 value)
{
	// Get client storage address.
	s8 * clientMemoryAddress = reinterpret_cast<s8*>(&mStorage[storageIndex]);

	// Write the value.
	*clientMemoryAddress = value;
}

u16 StorageObject_t::readHwordU(u32 storageIndex)
{
	// Get client storage address.
	u16 * clientMemoryAddress = reinterpret_cast<u16*>(&mStorage[storageIndex]);

	// Read the value.
	return *clientMemoryAddress;
}

void StorageObject_t::writeHwordU(u32 storageIndex, u16 value)
{
	// Get client storage address.
	u16 * clientMemoryAddress = reinterpret_cast<u16*>(&mStorage[storageIndex]);

	// Write the value.
	*clientMemoryAddress = value;
}

s16 StorageObject_t::readHwordS(u32 storageIndex)
{
	// Get client storage address.
	s16 * clientMemoryAddress = reinterpret_cast<s16*>(&mStorage[storageIndex]);

	// Read the value.
	return *clientMemoryAddress;
}

void StorageObject_t::writeHwordS(u32 storageIndex, s16 value)
{
	// Get client storage address.
	s16 * clientMemoryAddress = reinterpret_cast<s16*>(&mStorage[storageIndex]);

	// Write the value.
	*clientMemoryAddress = value;
}

u32 StorageObject_t::readWordU(u32 storageIndex)
{
	// Get client storage address.
	u32 * clientMemoryAddress = reinterpret_cast<u32*>(&mStorage[storageIndex]);

	// Read the value.
	return *clientMemoryAddress;
}

void StorageObject_t::writeWordU(u32 storageIndex, u32 value)
{
	// Get client storage address.
	u32 * clientMemoryAddress = reinterpret_cast<u32*>(&mStorage[storageIndex]);

	// Write the value.
	*clientMemoryAddress = value;
}

s32 StorageObject_t::readWordS(u32 storageIndex)
{
	// Get client storage address.
	s32 * clientMemoryAddress = reinterpret_cast<s32*>(&mStorage[storageIndex]);

	// Read the value.
	return *clientMemoryAddress;
}

void StorageObject_t::writeWordS(u32 storageIndex, s32 value)
{
	// Get client storage address.
	s32 * clientMemoryAddress = reinterpret_cast<s32*>(&mStorage[storageIndex]);

	// Write the value.
	*clientMemoryAddress = value;
}

u64 StorageObject_t::readDwordU(u32 storageIndex)
{
	// Get client storage address.
	u64 * clientMemoryAddress = reinterpret_cast<u64*>(&mStorage[storageIndex]);

	// Read the value.
	return *clientMemoryAddress;
}

void StorageObject_t::writeDwordU(u32 storageIndex, u64 value)
{
	// Get client storage address.
	u64 * clientMemoryAddress = reinterpret_cast<u64*>(&mStorage[storageIndex]);

	// Write the value.
	*clientMemoryAddress = value;
}

s64 StorageObject_t::readDwordS(u32 storageIndex)
{
	// Get client storage address.
	s64 * clientMemoryAddress = reinterpret_cast<s64*>(&mStorage[storageIndex]);

	// Read the value.
	return *clientMemoryAddress;
}

void StorageObject_t::writeDwordS(u32 storageIndex, s64 value)
{
	// Get client storage address.
	s64 * clientMemoryAddress = reinterpret_cast<s64*>(&mStorage[storageIndex]);

	// Write the value.
	*clientMemoryAddress = value;
}

size_t StorageObject_t::getStorageSize()
{
	return mStorageSize;
}

void* StorageObject_t::getClientMemoryAddress() const
{
	return reinterpret_cast<void*>(mStorage);
}
