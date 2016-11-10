#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The VIF R 0-3 register - Row filling data.
*/
class EEVifUnitRegister_R_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 R = 0;
	};

	EEVifUnitRegister_R_t();

};

/*
The VIF C 0-3 register - Column filling data.
*/
class EEVifUnitRegister_C_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 C = 0;
	};

	EEVifUnitRegister_C_t();

};

/*
The VIF CYCLE register - Data write cycle.
*/
class EEVifUnitRegister_CYCLE_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 CL = 0;
		static constexpr u8 WL = 1;
	};

	EEVifUnitRegister_CYCLE_t();

};

/*
The VIF MASK register - Write mask pattern.
*/
class EEVifUnitRegister_MASK_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 m0 = 0;
		static constexpr u8 m1 = 1;
		static constexpr u8 m2 = 2;
		static constexpr u8 m3 = 3;
		static constexpr u8 m4 = 4;
		static constexpr u8 m5 = 5;
		static constexpr u8 m6 = 6;
		static constexpr u8 m7 = 7;
		static constexpr u8 m8 = 8;
		static constexpr u8 m9 = 9;
		static constexpr u8 m10 = 10;
		static constexpr u8 m11 = 11;
		static constexpr u8 m12 = 12;
		static constexpr u8 m13 = 13;
		static constexpr u8 m14 = 14;
		static constexpr u8 m15 = 15;
	};

	EEVifUnitRegister_MASK_t();

};

/*
The VIF MODE register - Addition mode.
*/
class EEVifUnitRegister_MODE_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 MOD = 0;
	};

	EEVifUnitRegister_MODE_t();

};

/*
The VIF ITOP register - ITOP value.
*/
class EEVifUnitRegister_ITOP_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ITOP = 0;
	};

	EEVifUnitRegister_ITOP_t();

};

/*
The VIF ITOPS register - Following ITOP value.
*/
class EEVifUnitRegister_ITOPS_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ITOPS = 0;
	};

	EEVifUnitRegister_ITOPS_t();

};

/*
The VIF BASE register - Double buffer base address.
*/
class EEVifUnitRegister_BASE_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 BASE = 0;
	};

	EEVifUnitRegister_BASE_t();

};

/*
The VIF OFST register - Double buffer offset.
*/
class EEVifUnitRegister_OFST_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 OFFSET = 0;
	};

	EEVifUnitRegister_OFST_t();

};

/*
The VIF TOP register - TOP value.
*/
class EEVifUnitRegister_TOP_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 TOP = 0;
	};

	EEVifUnitRegister_TOP_t();

};

/*
The VIF TOPS register - Next TOP value / data write address.
*/
class EEVifUnitRegister_TOPS_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 TOPS = 0;
	};

	EEVifUnitRegister_TOPS_t();

};

/*
The VIF MARK register - Mark value.
*/
class EEVifUnitRegister_MARK_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 MARK = 0;
	};

	EEVifUnitRegister_MARK_t();

};

/*
The VIF NUM register - Amount of unwritten data.
*/
class EEVifUnitRegister_NUM_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 NUM = 0;
	};

	EEVifUnitRegister_NUM_t();

};

/*
The VIF CODE register - Most recently processed VIFcode.
*/
class EEVifUnitRegister_CODE_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 IMMEDIATE = 0;
		static constexpr u8 NUM = 1;
		static constexpr u8 CMD = 2;
	};

	EEVifUnitRegister_CODE_t();

};

/*
The VIF STAT register - VIF status.
Some fields are unused for the VIF0 unit (VGW, DBF and FDR).
*/
class EEVifUnitRegister_STAT_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 VPS = 0;
		static constexpr u8 VEW = 1;
		static constexpr u8 VGW = 2;
		static constexpr u8 MRK = 3;
		static constexpr u8 DBF = 4;
		static constexpr u8 VSS = 5;
		static constexpr u8 VFS = 6;
		static constexpr u8 VIS = 7;
		static constexpr u8 INT = 8;
		static constexpr u8 ER0 = 9;
		static constexpr u8 ER1 = 10;
		static constexpr u8 FDR = 11;
		static constexpr u8 FQC = 12;
	};

	EEVifUnitRegister_STAT_t();

};

/*
The VIF FBRST register - VIF operation control.
*/
class EEVifUnitRegister_FBRST_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 RST = 0;
		static constexpr u8 FBK = 1;
		static constexpr u8 STP = 2;
		static constexpr u8 STC = 3;
	};

	EEVifUnitRegister_FBRST_t();

};

/*
The VIF ERR register - VIF error status.
*/
class EEVifUnitRegister_ERR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 MII = 0;
		static constexpr u8 ME0 = 1;
		static constexpr u8 ME1 = 2;
	};

	EEVifUnitRegister_ERR_t();

};