MipsInstructionInfo INSTRUCTION_TABLE[90] =
{
    { "SLL", 29, CPI_R3000_DEFAULT },
    { "SRL", 30, CPI_R3000_DEFAULT },
    { "SRA", 31, CPI_R3000_DEFAULT },
    { "SLLV", 32, CPI_R3000_DEFAULT },
    { "SRLV", 33, CPI_R3000_DEFAULT },
    { "SRAV", 34, CPI_R3000_DEFAULT },
    { "JR", 35, CPI_R3000_BRANCH },
    { "JALR", 36, CPI_R3000_BRANCH },
    { "SYSCALL", 37, CPI_R3000_DEFAULT },
    { "BREAK", 38, CPI_R3000_DEFAULT },
    { "MFHI", 39, CPI_R3000_DEFAULT },
    { "MTHI", 40, CPI_R3000_DEFAULT },
    { "MFLO", 41, CPI_R3000_DEFAULT },
    { "MTLO", 42, CPI_R3000_DEFAULT },
    { "MULT", 43, CPI_R3000_MULTIPLY },
    { "MULTU", 44, CPI_R3000_MULTIPLY },
    { "DIV", 45, CPI_R3000_DIVIDE },
    { "DIVU", 46, CPI_R3000_DIVIDE },
    { "ADD", 47, CPI_R3000_DEFAULT },
    { "ADDU", 48, CPI_R3000_DEFAULT },
    { "SUB", 49, CPI_R3000_DEFAULT },
    { "SUBU", 50, CPI_R3000_DEFAULT },
    { "AND", 51, CPI_R3000_DEFAULT },
    { "OR", 52, CPI_R3000_DEFAULT },
    { "XOR", 53, CPI_R3000_DEFAULT },
    { "NOR", 54, CPI_R3000_DEFAULT },
    { "SLT", 55, CPI_R3000_DEFAULT },
    { "SLTU", 56, CPI_R3000_DEFAULT },
    { "BLTZ", 57, CPI_R3000_BRANCH },
    { "BGEZ", 58, CPI_R3000_BRANCH },
    { "BLTZAL", 59, CPI_R3000_BRANCH },
    { "BGEZAL", 60, CPI_R3000_BRANCH },
    { "MFC0", 61, CPI_COP_DEFAULT },
    { "CFC0", 62, CPI_COP_DEFAULT },
    { "MTC0", 63, CPI_COP_DEFAULT },
    { "CTC0", 64, CPI_COP_DEFAULT },
    { "RFE", 65, CPI_COP_DEFAULT },
    { "MFC2", 87, CPI_COP_DEFAULT },
    { "CFC2", 88, CPI_COP_DEFAULT },
    { "MTC2", 89, CPI_COP_DEFAULT },
    { "CTC2", 90, CPI_COP_DEFAULT },
    { "RTPS", 66, CPI_COP_DEFAULT },
    { "NCLIP", 67, CPI_COP_DEFAULT },
    { "OP", 68, CPI_COP_DEFAULT },
    { "DPCS", 69, CPI_COP_DEFAULT },
    { "INTPL", 70, CPI_COP_DEFAULT },
    { "MVMVA", 71, CPI_COP_DEFAULT },
    { "NCDS", 72, CPI_COP_DEFAULT },
    { "CDP", 73, CPI_COP_DEFAULT },
    { "NCDT", 74, CPI_COP_DEFAULT },
    { "NCCS", 75, CPI_COP_DEFAULT },
    { "CC", 76, CPI_COP_DEFAULT },
    { "NCS", 77, CPI_COP_DEFAULT },
    { "NCT", 78, CPI_COP_DEFAULT },
    { "SQR", 79, CPI_COP_DEFAULT },
    { "DCPL", 80, CPI_COP_DEFAULT },
    { "DPCT", 81, CPI_COP_DEFAULT },
    { "AVSZ3", 82, CPI_COP_DEFAULT },
    { "AVSZ4", 83, CPI_COP_DEFAULT },
    { "RTPT", 84, CPI_COP_DEFAULT },
    { "GPF", 85, CPI_COP_DEFAULT },
    { "GPL", 86, CPI_COP_DEFAULT },
    { "J", 1, CPI_R3000_BRANCH },
    { "JAL", 2, CPI_R3000_BRANCH },
    { "BEQ", 3, CPI_R3000_BRANCH },
    { "BNE", 4, CPI_R3000_BRANCH },
    { "BLEZ", 5, CPI_R3000_BRANCH },
    { "BGTZ", 6, CPI_R3000_BRANCH },
    { "ADDI", 7, CPI_R3000_DEFAULT },
    { "ADDIU", 8, CPI_R3000_DEFAULT },
    { "SLTI", 9, CPI_R3000_DEFAULT },
    { "SLTIU", 10, CPI_R3000_DEFAULT },
    { "ANDI", 11, CPI_R3000_DEFAULT },
    { "ORI", 12, CPI_R3000_DEFAULT },
    { "XORI", 13, CPI_R3000_DEFAULT },
    { "LUI", 14, CPI_R3000_DEFAULT },
    { "LB", 15, CPI_R3000_LOAD },
    { "LH", 16, CPI_R3000_LOAD },
    { "LWL", 17, CPI_R3000_LOAD },
    { "LW", 18, CPI_R3000_LOAD },
    { "LBU", 19, CPI_R3000_LOAD },
    { "LHU", 20, CPI_R3000_LOAD },
    { "LWR", 21, CPI_R3000_LOAD },
    { "SB", 22, CPI_R3000_STORE },
    { "SH", 23, CPI_R3000_STORE },
    { "SWL", 24, CPI_R3000_STORE },
    { "SW", 25, CPI_R3000_STORE },
    { "SWR", 26, CPI_R3000_STORE },
    { "LWC2", 27, CPI_R3000_LOAD },
    { "SWC2", 28, CPI_R3000_STORE },
};