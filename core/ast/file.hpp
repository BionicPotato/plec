#pragma once

#include "statementlist.hpp"
#include "../stmtstreams/file.hpp"

class File: public StatementList
{
    public:
	const char* const filename;
        File(std::vector<std::unique_ptr<const Statement>>&& statements, const char* const filename);
};

