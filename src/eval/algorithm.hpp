
namespace tungsten { namespace algorithm {

#ifdef TUNGSTEN_USE_MULTITHREADING

#include <parallel/algorithm>
using __gnu_parallel::for_each;

#else

#include <algorithm>

using std::for_each;

#endif


}} // namespace algorithm
