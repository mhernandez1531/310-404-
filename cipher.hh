// square_root.hh
// This header ensures C linkage is enforced when running C++ unit tessts on C code.

#ifdef __cplusplus

extern "C" {

#include "cipher.h"

}

#else

#include "cipher.h"

#endif

