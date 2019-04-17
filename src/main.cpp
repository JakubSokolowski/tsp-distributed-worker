#include <iostream>
#include "proto/message.pb.h"
#include <ostream>

int main() {
    message::Message m;
    m.set_id(0,1);
    std::cout << "Hello Proto!"  << std::endl;
    return 0;
}