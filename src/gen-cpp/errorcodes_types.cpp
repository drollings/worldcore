/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "errorcodes_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace ErrorCodes {

int _kCodeValues[] = {
  None,
  InvalidOffset,
  InvalidInput,
  InvalidPermissions,
  NullNotAllowed,
  OutOfRange,
  LengthExceeded,
  Unrecognized,
  Other,
  TOP
};
const char* _kCodeNames[] = {
  "None",
  "InvalidOffset",
  "InvalidInput",
  "InvalidPermissions",
  "NullNotAllowed",
  "OutOfRange",
  "LengthExceeded",
  "Unrecognized",
  "Other",
  "TOP"
};
const std::map<int, const char*> _Code_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(10, _kCodeValues, _kCodeNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

std::ostream& operator<<(std::ostream& out, const Code val) {
  std::map<int, const char*>::const_iterator it = _Code_VALUES_TO_NAMES.find(val);
  if (it != _Code_VALUES_TO_NAMES.end()) {
    out << it->second;
  } else {
    out << static_cast<int>(val);
  }
  return out;
}

} // namespace
