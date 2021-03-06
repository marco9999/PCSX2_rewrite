#pragma once

#include <functional>
#include <utility>

#include <Caches.hpp>

#include "Common/Types/Mips/MipsCoprocessor0.hpp"
#include "Common/Types/Mips/MmuAccess.hpp"

using OperatingContext = MipsCoprocessor0::OperatingContext;

/// Emulator translation cache, used to speed up virtual address translation.
/// Based around the MIPS translation process, using the current operating
/// context and instruction/data access. This works as there is a minimum TLB
/// page size (ie: 4KB on the EE Core), and everything else is a multiple of it.
/// The unmapped memory regions are usually aligned to this value (care must be taken).
template <int Size, typename AddressTy, AddressTy CacheMask, template <int, typename, typename> class CacheTy>
class TranslationCache
{
private:
    using CacheTy_ = CacheTy<Size, AddressTy, AddressTy>;

public:
    using FallbackFn = std::function<std::optional<AddressTy>(const AddressTy, const MmuRwAccess)>;

    TranslationCache() :
        fallback_fn(nullptr)
    {
    }

    /// Performs the virtual address to physical address translation.
    std::optional<AddressTy> lookup(const AddressTy virtual_address, const MmuRwAccess rw_access)
    {
        const AddressTy key = virtual_address & (~CacheMask);

        std::optional<AddressTy> result = cache.get(key);

        if (!result)
            result = handle_fallback(key, rw_access);

        if (result)
            *result = (*result | (virtual_address & CacheMask));

        return result;
    }

    /// Flushes the caches of all translation results.
    void flush()
    {
        cache = CacheTy_();
    }

    /// Sets the translation fallback function.
    void set_fallback_lookup(const FallbackFn& fallback_fn)
    {
        this->fallback_fn = fallback_fn;
    }

private:
    /// Performs a fallback lookup and inserts the result into the cache if its found.
    /// Returns the fallback result.
    std::optional<AddressTy> handle_fallback(const AddressTy key, const MmuRwAccess rw_access)
    {
        if (!fallback_fn)
            throw std::runtime_error("No fallback address translation function defined");

        std::optional<AddressTy> result = fallback_fn(key, rw_access);
        if (result)
            cache.insert(key, *result);

        return result;
    }

    FallbackFn fallback_fn;
    CacheTy_ cache;
};