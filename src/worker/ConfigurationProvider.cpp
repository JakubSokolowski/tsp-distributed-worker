#include "ConfigurationProvider.h"

SocketConfiguration ConfigurationProvider::GetConfiguration() const {
    return SocketConfiguration{42069, "127.0.0.1"};
}
