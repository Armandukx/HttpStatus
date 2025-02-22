# HttpStatus
A simple, header-only C++ library for working with HTTP status codes.

## Features
- Fast status code lookup with `std::unordered_map`
- Checks for status categories (Success, Redirection, Client Error, Server Error)
- Header-only

## Example
```cpp
#include "HttpStatus.hpp"

int main() {
    int code = 404; // HTTP status code example
    
    // Print the reason phrase for the given status code
    printf("HTTP Status %d: %s\n", code, HttpStatus::GetHttpStatusReason(code).c_str());
    
    // Check if the status code indicates a successful response (2xx)
    if (HttpStatus::IsSuccess(code)) {
        printf("%d is a success status!\n", code);
    } else {
        printf("%d is not a success status.\n", code); // It's not a success (since 404 is a client error)
    }

    return 0;
}
```
Output:
```
HTTP Status 404: Not Found
404 is not a success status.
```

## License
MIT License
