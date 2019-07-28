#include "fdsmedian.h"

#include <gossort.h>

namespace fds {
namespace statistics {
Median::Median() {
  reset();
}
void Median::reset() {
  count_ = 0;
  index_ = MEDIAN_COUNT;
  for (uint8_t i = 0; i < MEDIAN_COUNT; i++) {
    r_[i] = i;
  }
  iscache_ = false;
}
void Median::clearallbutlast() {
  MEDIAN_TYPE last = values_[index_];
  reset();
  add(last);
}
bool Median::add(const MEDIAN_TYPE & value) {
  iscache_ = false;
  index_ = index_ < MEDIAN_COUNT - 1 ? index_ + 1 : 0;
  values_[index_] = value;
  if (count_ < MEDIAN_COUNT) {
    count_++;
    return false;
  } else {
    return true;
  }
}

MEDIAN_TYPE Median::get() {
  if (!iscache_) {
    switch (count_) {
    case 0:
      median_ = MEDIAN_UNDEFINED;
      break;
    case 1:
      median_ = values_[0];
      break;
    case 2:
      median_ = (values_[0] + values_[1]) / 2.0F;
      break;
    default:
      gos::sort::real::reference::insertion(values_, r_, count_);
      if (count_ & 0x01)
        median_ = values_[r_[count_ / 2]];
      else
        median_ = (values_[r_[count_ / 2]] + values_[r_[count_ / 2 - 1]]) / 2.0F;
      break;
    }
    iscache_ = true;
  }
  return median_;
}

}
}
