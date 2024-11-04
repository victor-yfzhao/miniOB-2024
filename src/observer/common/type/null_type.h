/**
 * self-defined data type: Null
 */

#pragma once

#include "common/rc.h"
#include "common/type/data_type.h"

/**
 * @brief 日期类型
 * @ingroup DataType
 */
class NullType : public DataType
{
public:
  NullType() : DataType(AttrType::NULLS) {}

  virtual ~NullType() = default;

  // int compare(const Value &left, const Value &right) const override;

  bool is_null(const Value &val) const override;

  // RC subtract(const Value &left, const Value &right, Value &result) const override;

  RC cast_to(const Value &val, AttrType type, Value &result) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  // int cast_cost(AttrType type) override;

  RC to_string(const Value &val, string &result) const override;

private:
  const std::string null_str_ = "NULL";
};