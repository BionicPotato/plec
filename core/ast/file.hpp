#pragma once

#include "statementlist.hpp"
#include "../stmtstreams/file.hpp"

class File: public StatementList
{
    public:
	const char* filename;
        File(const char* filename);
};
