#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

int main() {
    for (int i = 1; i <= 100; ++i) {
        std::ostringstream filename;
        filename << "error_log_" << std::setw(3) << std::setfill('0') << i << ".txt";
        std::ofstream file(filename.str());
        file << "System Error: 0x" << std::hex << (1000 + i*13) << "\n";
        file << "Critical failure at address 0x" << std::hex << (0xDEADBEEF + i*100) << "\n";
        file << "Stack trace:\n";
        file << "  at module.dll+0x" << std::hex << (0x1000 + i*5) << "\n";
        file << "  at kernel32.dll+0x" << std::hex << (0x2000 + i*7) << "\n";
        file << "Please contact your administrator.\n";
        file.close();
    }
    return 0;
}