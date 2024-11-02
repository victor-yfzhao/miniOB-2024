#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/date_type.h"
#include "common/value.h"

int DateType::compare(const Value &left, const Value &right) const
{
  if(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS) {
    return INT32_MAX;
  }
  if(right.attr_type() == AttrType::CHARS) {
    Value tmp;
    RC rc = set_value_from_str(tmp, right.get_string());
    if(rc != RC::SUCCESS) {
      LOG_WARN("Failed to set value from string. rc=%d", rc);
      return INT32_MAX;
    }
    return common::compare_int((void *)&left.value_.int_value_, (void *)&tmp.value_.int_value_);
  }
  return common::compare_int((void *)&left.value_.int_value_, (void *)&right.value_.int_value_);
}

RC DateType::set_value_from_str(Value &val, const string &data) const
{
  if (data.size() < 8 || data.size() > 10) {
    return RC::INVALID_ARGUMENT;
  }

  size_t first_dash = data.find('-');
  size_t second_dash = data.find('-', first_dash + 1);

  if (first_dash == string::npos || second_dash == string::npos) {
    return RC::INVALID_ARGUMENT;
  }

  int year, month, day;
  try {
    year = stoi(data.substr(0, first_dash));
    month = stoi(data.substr(first_dash + 1, second_dash - first_dash - 1));
    day = stoi(data.substr(second_dash + 1));
  } catch (const exception &e) {
    return RC::INVALID_ARGUMENT;
  }

  if (month < 1 || month > 12 || day < 1 || day > 31) {
    return RC::INVALID_ARGUMENT;
  }

  // Check for days in month
  static const int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  if (month == 2) {
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (day > (is_leap ? 29 : 28)) {
      return RC::INVALID_ARGUMENT;
    }
  } else if (day > days_in_month[month - 1]) {
    return RC::INVALID_ARGUMENT;
  }

  val.value_.int_value_ = year * 10000 + month * 100 + day;
  return RC::SUCCESS;
}


RC DateType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::DATES: {
      result = val;
    } break;
    case AttrType::CHARS: {
      return RC::UNIMPLEMENTED;
    } break;
    default: return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

// int CharType::cast_cost(AttrType type)
// {
//   if (type == AttrType::CHARS) {
//     return 0;
//   }
//   return INT32_MAX;
// }

RC DateType::to_string(const Value &val, string &result) const
{
    int date = val.value_.int_value_;
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", year, month, day);
    result = buffer;

    return RC::SUCCESS;
}