#pragma once

#include <string>

#ifdef NDEBUG

#define ASSERT(condition) ((void)0)
#define ASSERT_MSG(condition, message) ((void)0)

#else

#define ASSERT(condition) _assert((condition), #condition, __FILE__, __LINE__, __func__)
#define ASSERT_MSG(condition, message) _assert((condition), #condition, __FILE__, __LINE__, __func__, message)

#endif //NDEBUG

void _assert(bool condition,
			const std::string& conditionString,
			const std::string& filename,
			int line,
			const std::string& function);

void _assert(bool condition,
			const std::string& conditionString,
			const std::string& filename,
			int line,
			const std::string& function, 
			const std::string& message);