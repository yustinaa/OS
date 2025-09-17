#include "creator_func.h"
#include <fstream>

bool writeEmployeesToFile(const std::string& filename, const std::vector<employee>& employees) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) return false;

    for (const auto& e : employees) {
        out.write(reinterpret_cast<const char*>(&e), sizeof(employee));
    }
    return true;
}
