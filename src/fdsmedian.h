#ifndef _FDS_ARDUINO_LIBRARY_MEDIAN_H_
#define _FDS_ARDUINO_LIBRARY_MEDIAN_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "Arduino.h"
//#include "WProgram.h"
#endif

#define FDS_MEDIAN_VERSION "0.0.1"

// should at least be 5 to be practical
// odd size results in a 'real' middle element.
// even size takes the lower of the two middle elements
#ifndef MEDIAN_COUNT
#define MEDIAN_COUNT 8
#endif

#ifndef MEDIAN_UNDEFINED
#define MEDIAN_UNDEFINED NAN
#endif

#ifndef MEDIAN_TYPE
#define MEDIAN_TYPE float
#endif

#ifndef MEDIAN_SORT
#define MEDIAN_SORT bubblesort
#endif

namespace fds {
namespace statistics {
class Median {
public:
  Median();
  void reset();
  void clearallbutlast();
  bool add(const MEDIAN_TYPE & value);
  MEDIAN_TYPE median();  // returns the median == middle element
protected:
  uint8_t count_;
  uint8_t index_;
  bool issorted_;
  MEDIAN_TYPE values_[MEDIAN_COUNT];
  uint8_t p_[MEDIAN_COUNT];
#if MEDAIN_SORT == bubblesort
  void bubblesort();
#else
  void insertionsort();
#endif
};
}
}
#endif /* _FDS_ARDUINO_LIBRARY_MEDIAN_H_ */
