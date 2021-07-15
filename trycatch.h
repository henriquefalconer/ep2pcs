#include <functional>
#include <stdexcept>

using namespace std;

using voidfunc = function<void()>;

inline void tryCatch(voidfunc t, voidfunc c = []() {}) {
    try {
        t();
    } catch (exception* e) {
        c();
        delete e;
    }
}
