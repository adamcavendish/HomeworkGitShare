#pragma once

enum Command {
    CMD_IA,     // Insert into Set A
    CMD_DA,     // Delete from Set A
    CMD_IB,     // Insert into Set B
    CMD_DB,     // Delete from Set B
    CMD_OU,     // Union of Set A and Set B
    CMD_OI,     // Intersection of Set A and Set B
    CMD_OD,     // Difference of Set A and Set B
    CMD_Q       // Quit
};//Command

