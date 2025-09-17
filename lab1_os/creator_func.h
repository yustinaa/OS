#pragma once
#include "employee.h"
#include <string>
#include <vector>

bool writeEmployeesToFile(const std::string& filename, const std::vector<employee>& employees);
