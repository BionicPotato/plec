#include "file.hpp"

File::File(std::vector<std::unique_ptr<const Statement>>&& statements, const char* filename)
: StatementList(std::move(statements)), filename(filename) {}

