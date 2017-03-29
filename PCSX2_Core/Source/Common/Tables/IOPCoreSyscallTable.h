#pragma once

#include "Common/Global/Globals.h"

/*
Lists the IOPCore's OS list of syscalls available (mnemonics).
*/
struct IOPCoreSyscallTable
{
	struct IOPCoreSyscallInfo_t
	{
		const char * mMnemonic;
	};

	static constexpr IOPCoreSyscallInfo_t IOPCORE_SYSCALL_TABLE[Constants::IOP::IOPCore::R3000::NUMBER_SYSCALLS] =
	{
		{ "Unknown" }, // 000.
		{ "CpuDisableIntr" }, // 001.
		{ "CpuEnableIntr" }, // 002.
		{ "intrman_call14" }, // 003.
		{ "intrman_call17_19" }, // 004.
		{ "intrman_call18_20" }, // 005.
		{ "Unknown" }, // 006.
		{ "Unknown" }, // 007.
		{ "threadman" }, // 008.
		{ "Unknown" }, // 009.
		{ "Unknown" }, // 010.
		{ "Unknown" }, // 011.
		{ "Unknown" }, // 012.
		{ "Unknown" }, // 013.
		{ "Unknown" }, // 014.
		{ "Unknown" }, // 015.
		{ "Unknown" }, // 016.
		{ "Unknown" }, // 017.
		{ "Unknown" }, // 018.
		{ "Unknown" }, // 019.
		{ "Unknown" }, // 020.
		{ "Unknown" }, // 021.
		{ "Unknown" }, // 022.
		{ "Unknown" }, // 023.
		{ "Unknown" }, // 024.
		{ "Unknown" }, // 025.
		{ "Unknown" }, // 026.
		{ "Unknown" }, // 027.
		{ "Unknown" }, // 028.
		{ "Unknown" }, // 029.
		{ "Unknown" }, // 030.
		{ "Unknown" }, // 031.
		{ "Unknown" }, // 032.
		{ "Unknown" }, // 033.
		{ "Unknown" }, // 034.
		{ "Unknown" }, // 035.
		{ "Unknown" }, // 036.
		{ "Unknown" }, // 037.
		{ "Unknown" }, // 038.
		{ "Unknown" }, // 039.
		{ "Unknown" }, // 040.
		{ "Unknown" }, // 041.
		{ "Unknown" }, // 042.
		{ "Unknown" }, // 043.
		{ "Unknown" }, // 044.
		{ "Unknown" }, // 045.
		{ "Unknown" }, // 046.
		{ "Unknown" }, // 047.
		{ "Unknown" }, // 048.
		{ "Unknown" }, // 049.
		{ "Unknown" }, // 050.
		{ "Unknown" }, // 051.
		{ "Unknown" }, // 052.
		{ "Unknown" }, // 053.
		{ "Unknown" }, // 054.
		{ "Unknown" }, // 055.
		{ "Unknown" }, // 056.
		{ "Unknown" }, // 057.
		{ "Unknown" }, // 058.
		{ "Unknown" }, // 059.
		{ "Unknown" }, // 060.
		{ "Unknown" }, // 061.
		{ "Unknown" }, // 062.
		{ "Unknown" }, // 063.
		{ "Unknown" }, // 064.
		{ "Unknown" }, // 065.
		{ "Unknown" }, // 066.
		{ "Unknown" }, // 067.
		{ "Unknown" }, // 068.
		{ "Unknown" }, // 069.
		{ "Unknown" }, // 070.
		{ "Unknown" }, // 071.
		{ "Unknown" }, // 072.
		{ "Unknown" }, // 073.
		{ "Unknown" }, // 074.
		{ "Unknown" }, // 075.
		{ "Unknown" }, // 076.
		{ "Unknown" }, // 077.
		{ "Unknown" }, // 078.
		{ "Unknown" }, // 079.
		{ "Unknown" }, // 080.
		{ "Unknown" }, // 081.
		{ "Unknown" }, // 082.
		{ "Unknown" }, // 083.
		{ "Unknown" }, // 084.
		{ "Unknown" }, // 085.
		{ "Unknown" }, // 086.
		{ "Unknown" }, // 087.
		{ "Unknown" }, // 088.
		{ "Unknown" }, // 089.
		{ "Unknown" }, // 090.
		{ "Unknown" }, // 091.
		{ "Unknown" }, // 092.
		{ "Unknown" }, // 093.
		{ "Unknown" }, // 094.
		{ "Unknown" }, // 095.
		{ "Unknown" }, // 096.
		{ "Unknown" }, // 097.
		{ "Unknown" }, // 098.
		{ "Unknown" }, // 099.
		{ "Unknown" }, // 100.
		{ "Unknown" }, // 101.
		{ "Unknown" }, // 102.
		{ "Unknown" }, // 103.
		{ "Unknown" }, // 104.
		{ "Unknown" }, // 105.
		{ "Unknown" }, // 106.
		{ "Unknown" }, // 107.
		{ "Unknown" }, // 108.
		{ "Unknown" }, // 109.
		{ "Unknown" }, // 110.
		{ "Unknown" }, // 111.
		{ "Unknown" }, // 112.
		{ "Unknown" }, // 113.
		{ "Unknown" }, // 114.
		{ "Unknown" }, // 115.
		{ "Unknown" }, // 116.
		{ "Unknown" }, // 117.
		{ "Unknown" }, // 118.
		{ "Unknown" }, // 119.
		{ "Unknown" }, // 120.
		{ "Unknown" }, // 121.
		{ "Unknown" }, // 122.
		{ "Unknown" }, // 123.
		{ "Unknown" }, // 124.
		{ "Unknown" }, // 125.
		{ "Unknown" }, // 126.
		{ "Unknown" }, // 127.
		{ "Unknown" }, // 128.
		{ "Unknown" }, // 129.
		{ "Unknown" }, // 130.
		{ "Unknown" }, // 131.
		{ "Unknown" }, // 132.
		{ "Unknown" }, // 133.
		{ "Unknown" }, // 134.
		{ "Unknown" }, // 135.
		{ "Unknown" }, // 136.
		{ "Unknown" }, // 137.
		{ "Unknown" }, // 138.
		{ "Unknown" }, // 139.
		{ "Unknown" }, // 140.
		{ "Unknown" }, // 141.
		{ "Unknown" }, // 142.
		{ "Unknown" }, // 143.
		{ "Unknown" }, // 144.
		{ "Unknown" }, // 145.
		{ "Unknown" }, // 146.
		{ "Unknown" }, // 147.
		{ "Unknown" }, // 148.
		{ "Unknown" }, // 149.
		{ "Unknown" }, // 150.
		{ "Unknown" }, // 151.
		{ "Unknown" }, // 152.
		{ "Unknown" }, // 153.
		{ "Unknown" }, // 154.
		{ "Unknown" }, // 155.
		{ "Unknown" }, // 156.
		{ "Unknown" }, // 157.
		{ "Unknown" }, // 158.
		{ "Unknown" }, // 159.
		{ "Unknown" }, // 160.
		{ "Unknown" }, // 161.
		{ "Unknown" }, // 162.
		{ "Unknown" }, // 163.
		{ "Unknown" }, // 164.
		{ "Unknown" }, // 165.
		{ "Unknown" }, // 166.
		{ "Unknown" }, // 167.
		{ "Unknown" }, // 168.
		{ "Unknown" }, // 169.
		{ "Unknown" }, // 170.
		{ "Unknown" }, // 171.
		{ "Unknown" }, // 172.
		{ "Unknown" }, // 173.
		{ "Unknown" }, // 174.
		{ "Unknown" }, // 175.
		{ "Unknown" }, // 176.
		{ "Unknown" }, // 177.
		{ "Unknown" }, // 178.
		{ "Unknown" }, // 179.
		{ "Unknown" }, // 180.
		{ "Unknown" }, // 181.
		{ "Unknown" }, // 182.
		{ "Unknown" }, // 183.
		{ "Unknown" }, // 184.
		{ "Unknown" }, // 185.
		{ "Unknown" }, // 186.
		{ "Unknown" }, // 187.
		{ "Unknown" }, // 188.
		{ "Unknown" }, // 189.
		{ "Unknown" }, // 190.
		{ "Unknown" }, // 191.
		{ "Unknown" }, // 192.
		{ "Unknown" }, // 193.
		{ "Unknown" }, // 194.
		{ "Unknown" }, // 195.
		{ "Unknown" }, // 196.
		{ "Unknown" }, // 197.
		{ "Unknown" }, // 198.
		{ "Unknown" }, // 199.
		{ "Unknown" }, // 200.
		{ "Unknown" }, // 201.
		{ "Unknown" }, // 202.
		{ "Unknown" }, // 203.
		{ "Unknown" }, // 204.
		{ "Unknown" }, // 205.
		{ "Unknown" }, // 206.
		{ "Unknown" }, // 207.
		{ "Unknown" }, // 208.
		{ "Unknown" }, // 209.
		{ "Unknown" }, // 210.
		{ "Unknown" }, // 211.
		{ "Unknown" }, // 212.
		{ "Unknown" }, // 213.
		{ "Unknown" }, // 214.
		{ "Unknown" }, // 215.
		{ "Unknown" }, // 216.
		{ "Unknown" }, // 217.
		{ "Unknown" }, // 218.
		{ "Unknown" }, // 219.
		{ "Unknown" }, // 220.
		{ "Unknown" }, // 221.
		{ "Unknown" }, // 222.
		{ "Unknown" }, // 223.
		{ "Unknown" }, // 224.
		{ "Unknown" }, // 225.
		{ "Unknown" }, // 226.
		{ "Unknown" }, // 227.
		{ "Unknown" }, // 228.
		{ "Unknown" }, // 229.
		{ "Unknown" }, // 230.
		{ "Unknown" }, // 231.
		{ "Unknown" }, // 232.
		{ "Unknown" }, // 233.
		{ "Unknown" }, // 234.
		{ "Unknown" }, // 235.
		{ "Unknown" }, // 236.
		{ "Unknown" }, // 237.
		{ "Unknown" }, // 238.
		{ "Unknown" }, // 239.
		{ "Unknown" }, // 240.
		{ "Unknown" }, // 241.
		{ "Unknown" }, // 242.
		{ "Unknown" }, // 243.
		{ "Unknown" }, // 244.
		{ "Unknown" }, // 245.
		{ "Unknown" }, // 246.
		{ "Unknown" }, // 247.
		{ "Unknown" }, // 248.
		{ "Unknown" }, // 249.
		{ "Unknown" }, // 250.
		{ "Unknown" }, // 251.
		{ "Unknown" }, // 252.
		{ "Unknown" }, // 253.
		{ "Unknown" }, // 254.
		{ "Unknown" }, // 255.
	};

	/*
	Returns the syscall properties from above given the syscall number.
	*/
	static const IOPCoreSyscallInfo_t * getSyscallInfo(const int syscallNumber);
};

