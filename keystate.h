#ifndef KEYSTATE_H
#define KEYSTATE_H

namespace engine
{
    struct keystate
    {
        int value;

        // Constructor to initialize value easily
        explicit keystate(int v = 0) : value(v) {}

        // Bool conversion: false if 0 or -1
        operator bool() const {
            return value != 0 && value != -1;
        }
        
        bool operator!() const {
            return !value;
        }

        // Equality operator
        bool operator==(const keystate& a) const {
            return value == a.value;
        }

        // Inequality operator
        bool operator!=(const keystate& a) const {
            return value != a.value;
        }
        
        bool operator==(const int &a) const {
            return value == a;
        }
        
        bool operator!=(const int &a) const {
            return value != a;
        }
    };
    
    // Define constant keystate instances
    inline const keystate KEYSTATE_UNKNOWN(-1);
    inline const keystate KEYSTATE_RELEASE(0);
    inline const keystate KEYSTATE_PRESS(1);
    inline const keystate KEYSTATE_HOLD(2);
}

#endif
