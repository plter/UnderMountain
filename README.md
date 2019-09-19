# UnderMountain
UnderMountain is a full-stack async web server framework


# HelloWorld 

```cpp
#include <um.h>
#include <boost/asio/use_awaitable.hpp>

int main() {
    um::Server server(9000, [](auto req, auto res) -> boost::asio::awaitable<void> {
        co_await res->end("Hello World");
    });
}
```

