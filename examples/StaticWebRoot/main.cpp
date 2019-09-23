//
// Created by plter on 2019/9/21.
//

#include <um.h>
#include <map>
#include <string>
#include <any>

int main() {
    um::Server server(9000);
    server.getFilterChain()->addFilter(std::make_shared<um::FilterStaticFiles>("static"));
    server.start();
    return 0;
}