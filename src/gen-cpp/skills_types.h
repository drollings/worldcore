/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef skills_TYPES_H
#define skills_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>


namespace Skills {

enum Flags {
  LEARNABLE = 1,
  STAT = 2,
  SKILL = 4,
  PRAYER = 8,
  COMBATMOVE = 16,
  WEAPONPROF = 32,
  LANGUAGE = 64,
  STEALTH = 128,
  MAGICROOT = 256,
  MAGICMETHOD = 512,
  MAGICTECHNIQUE = 1024,
  MAGICSPELL = 2048,
  ORDINATION = 4096,
  SPHERE = 8192,
  VOW = 16384,
  PSI = 32768,
  DEFAULT = 65536
};

extern const std::map<int, const char*> _Flags_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const Flags val);

enum Targets {
  Ignore = 1,
  CharRoom = 2,
  CharWorld = 4,
  FightSelf = 8,
  FightVict = 16,
  SelfOnly = 32,
  NotSelf = 64,
  ObjInv = 128,
  ObjRoom = 256,
  ObjWorld = 512,
  ObjEquip = 1024,
  ObjDest = 2048,
  CharObj = 4096,
  IgnChar = 8192,
  IgnObj = 16384,
  Melee = 32768,
  Ranged = 65536
};

extern const std::map<int, const char*> _Targets_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const Targets val);

enum Stats {
  SKLBASE_STR = 1,
  SKLBASE_INT = 2,
  SKLBASE_AGI = 4,
  SKLBASE_HT = 8,
  SKLBASE_VISION = 16,
  SKLBASE_HEARING = 32,
  SKLBASE_MOVE = 64
};

extern const std::map<int, const char*> _Stats_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const Stats val);

enum StatBases {
  STAT_STR = 0,
  STAT_INT = 1,
  STAT_AGI = 2,
  STAT_HT = 3,
  STAT_VISION = 4,
  STAT_HEARING = 5,
  STAT_MOVE = 6,
  STAT_MAX = 7,
  TOP = 8
};

extern const std::map<int, const char*> _StatBases_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const StatBases val);

} // namespace

#endif
