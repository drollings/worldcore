/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "proximities_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace Proximities {

int _kProximitiesValues[] = {
  INSIDE,
  PEOPLE,
  EQUIPPED,
  LOCATION,
  PROPERTYOF,
  SOUGHT,
  REMEMBERED,
  TARGETED,
  AFFECTING,
  CONCENTRATING,
  FOLLOWING,
  STALKING,
  MEMBEROF,
  LISTENER,
  TOP
};
const char* _kProximitiesNames[] = {
  "INSIDE",
  "PEOPLE",
  "EQUIPPED",
  "LOCATION",
  "PROPERTYOF",
  "SOUGHT",
  "REMEMBERED",
  "TARGETED",
  "AFFECTING",
  "CONCENTRATING",
  "FOLLOWING",
  "STALKING",
  "MEMBEROF",
  "LISTENER",
  "TOP"
};
const std::map<int, const char*> _Proximities_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(15, _kProximitiesValues, _kProximitiesNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

std::ostream& operator<<(std::ostream& out, const Proximities val) {
  std::map<int, const char*>::const_iterator it = _Proximities_VALUES_TO_NAMES.find(val);
  if (it != _Proximities_VALUES_TO_NAMES.end()) {
    out << it->second;
  } else {
    out << static_cast<int>(val);
  }
  return out;
}

} // namespace
