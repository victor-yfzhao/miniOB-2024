#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/null_type.h"
#include "common/value.h"

int NullType::compare(const Value &left, const Value &right) const
{
  bool left_is_null = left.attr_type() == AttrType::NULLS;
  bool right_is_null = right.attr_type() == AttrType::NULLS;
  if (left_is_null && right_is_null) {
    return 0;
  } 
  return 1;
}

RC NullType::set_value_from_str(Value &val, const string &data) const
{
  return RC::UNSUPPORTED;
}


RC NullType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::NULLS:
      result = val;
      break;
    default: return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

RC NullType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << null_str_;
  result = ss.str();
  return RC::SUCCESS;
}