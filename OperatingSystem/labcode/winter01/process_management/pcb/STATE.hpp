#pragma once

// C-STL
#include <cstdint>

enum struct STATE : std::int8_t
{
	TASK_INTERRUPTIBLE,
	TASK_RUNNING,
	TASK_DEAD
};

