#include "cmath"
#include "iostream"
#include <comm>

#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/operators.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/weak_ptr.hpp>

#include "/usr/share/emscripten/cache/sysroot/include/c++/v1/math.h"

namespace std {
template <typename _Tp, bool = std::__is_integer<_Tp>::__value>
struct __promote {
  typedef double __type;
};
} // namespace std

typedef __gnu_cxx::__promote<class _A1> sdwd;

int main() {
  boost::int8_t num1;
  printf("Hello World!\n");
  std::isnormal(2);

  std::__promote<int> sw{};
}