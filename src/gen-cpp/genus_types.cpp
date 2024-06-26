/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "genus_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace Genus {

int _kGenusValues[] = {
  UNDEFINED,
  INT,
  TYPE,
  FLAGS,
  STRING,
  SSTRING,
  LEXISTRING,
  CONSTRAINT,
  EDITABLE,
  ELEMENT,
  THING,
  LOCATION,
  SKILLSTORE,
  VEGETABLE,
  CREATURE,
  WORLD,
  AFFECT,
  EVENT,
  CONCENTRATION,
  PROPERTY,
  ACTION,
  EXIT,
  MIND,
  TOP
};
const char* _kGenusNames[] = {
  "UNDEFINED",
  "INT",
  "TYPE",
  "FLAGS",
  "STRING",
  "SSTRING",
  "LEXISTRING",
  "CONSTRAINT",
  "EDITABLE",
  "ELEMENT",
  "THING",
  "LOCATION",
  "SKILLSTORE",
  "VEGETABLE",
  "CREATURE",
  "WORLD",
  "AFFECT",
  "EVENT",
  "CONCENTRATION",
  "PROPERTY",
  "ACTION",
  "EXIT",
  "MIND",
  "TOP"
};
const std::map<int, const char*> _Genus_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(24, _kGenusValues, _kGenusNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

std::ostream& operator<<(std::ostream& out, const Genus val) {
  std::map<int, const char*>::const_iterator it = _Genus_VALUES_TO_NAMES.find(val);
  if (it != _Genus_VALUES_TO_NAMES.end()) {
    out << it->second;
  } else {
    out << static_cast<int>(val);
  }
  return out;
}

} // namespace
