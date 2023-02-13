#include "SLib/SLib.hpp"

int main() {
    S_LOG_LEVEL_ERROR;

    S_TRACE("TRACE!");
    S_INFO("INFO!");
    S_WARNING("WARNING!");
    S_ERROR("ERROR!");
    S_FATAL("FATAL!");

    return 0;
}
