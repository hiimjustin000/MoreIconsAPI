# More Icons API
A mod that provides an API for the More Icons mod.

## Usage
To use this API in your mod, add the following to your `mod.json`:
```json
{
    "dependencies": [
        {
            "id": "hiimjustin000.more_icons_api",
            "version": ">=v1.0.0",
            "importance": "required"
        }
    ]
}
```

You can then include the API in your code like so:
```cpp
#include <hiimjustin000.more_icons_api/MoreIconsAPI.hpp>
```

Further documentation can be found [here](./include/MoreIconsAPI.hpp).

# License
This mod is licensed under the [MIT License](./LICENSE).