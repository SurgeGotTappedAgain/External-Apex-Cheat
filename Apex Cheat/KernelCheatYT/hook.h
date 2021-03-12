#pragma once
#include "memory.h"

namespace nullhook
{
	bool call_kernel_function(void* kernel_function_address);
	NTSTATUS hook_handler(PVOID called_param);
}