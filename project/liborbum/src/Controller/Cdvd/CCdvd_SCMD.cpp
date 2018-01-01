#include "Core.hpp"

#include "Controller/Cdvd/CCdvd.hpp"

#include "Resources/RResources.hpp"

void CCdvd::SCMD_INSTRUCTION_15() const
{
	auto& r = core->get_resources();

	// Return magic value.
	r.cdvd.s_data_out.write_ubyte(0x5);
}

void CCdvd::SCMD_INSTRUCTION_40() const
{
	auto& r = core->get_resources();

	// Read config parameters.
	ubyte read_write = r.cdvd.s_rdy_din.data_in.read_ubyte();
	ubyte area = r.cdvd.s_rdy_din.data_in.read_ubyte();
	ubyte max_blocks = r.cdvd.s_rdy_din.data_in.read_ubyte();

	// Set NVRAM config parameters.
	r.cdvd.nvram.set_access_params(read_write, area, max_blocks, 0);

	// Return success.
	r.cdvd.s_data_out.write_ubyte(0);
}

void CCdvd::SCMD_INSTRUCTION_41() const
{
	auto& r = core->get_resources();

	// Read and return config block data.
	// A block is 16 bytes / 8 hwords long.
	// TODO: check for endianess problems.
	uhword buffer[8];
	r.cdvd.nvram.read_config_block(buffer);
	r.cdvd.s_data_out.write(reinterpret_cast<ubyte*>(buffer), 16);
}

void CCdvd::SCMD_INSTRUCTION_42() const
{
	auto& r = core->get_resources();
	
	// Write config data block and return success.
	// A block is 16 bytes / 8 hwords long.
	// TODO: check for endianess problems.
	uhword buffer[8];
	r.cdvd.s_rdy_din.data_in.read(reinterpret_cast<ubyte*>(buffer), 16);
	r.cdvd.nvram.write_config_block(buffer);
	r.cdvd.s_data_out.write_ubyte(0);
}

void CCdvd::SCMD_INSTRUCTION_43() const
{
	auto& r = core->get_resources();

	// Reset config parameters and return success.
	r.cdvd.nvram.set_access_params(0, 0, 0, 0);
	r.cdvd.s_data_out.write_ubyte(0);
}
