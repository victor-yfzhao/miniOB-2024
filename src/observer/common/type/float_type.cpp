/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/float_type.h"
#include "common/value.h"
#include "common/lang/limits.h"
#include "common/value.h"
#include "float_type.h"

int FloatType::compare(const Value &left, const Value &right) const
{
  if (left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS) {
    return INT32_MAX;
  }

  ASSERT(left.attr_type() == AttrType::FLOATS, "left type is not integer");
  ASSERT(right.attr_type() == AttrType::INTS || right.attr_type() == AttrType::FLOATS || right.attr_type() == AttrType::NULLS, "right type is not numeric");
  float left_val  = left.get_float();
  float right_val = right.get_float();
  if (right.attr_type() == AttrType::NULLS) {
    return INT32_MAX;
  }
  return common::compare_float((void *)&left_val, (void *)&right_val);
}

RC FloatType::add(const Value &left, const Value &right, Value &result) const
{
  if (right.attr_type() == AttrType::NULLS) {
    result.set_null();
    return RC::SUCCESS;
  }
  result.set_float(left.get_float() + right.get_float());
  return RC::SUCCESS;
}
RC FloatType::subtract(const Value &left, const Value &right, Value &result) const
{
  result.set_float(left.get_float() - right.get_float());
  return RC::SUCCESS;
}
RC FloatType::multiply(const Value &left, const Value &right, Value &result) const
{
  result.set_float(left.get_float() * right.get_float());
  return RC::SUCCESS;
}

RC FloatType::divide(const Value &left, const Value &right, Value &result) const
{
  if (right.get_float() > -EPSILON && right.get_float() < EPSILON) {
    // NOTE:
    // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
    result.set_null();
  } else {
    result.set_float(left.get_float() / right.get_float());
  }
  return RC::SUCCESS;
}

RC FloatType::negative(const Value &val, Value &result) const
{
  result.set_float(-val.get_float());
  return RC::SUCCESS;
}

RC FloatType::set_value_from_str(Value &val, const string &data) const
{
  LOG_INFO("OTHER TYPES TO FLOATS %s ",data);
  RC                rc = RC::SUCCESS;
  // stringstream deserialize_stream;
  // deserialize_stream.clear();
  // deserialize_stream.str(data);
  
  // float float_value;
  // deserialize_stream >> float_value;
  // if (!deserialize_stream || !deserialize_stream.eof()) {
  //   rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  // } else {
  //   val.set_float(float_value);
  // }
  try {
    float float_value = std::stof(data);  // 使用 std::stof 进行字符串到 float 的转换
    val.set_float(float_value);           // 成功转换后，设置到 Value 对象
    return RC::SUCCESS;
  } catch (const std::invalid_argument& e) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;  // 返回类型不匹配的错误
  } catch (const std::out_of_range& e) {
    return RC::INVALID_ARGUMENT;  // 返回数值超出范围的错误
  }
  return rc;
}

RC FloatType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << common::double_to_str(val.value_.float_value_);
  result = ss.str();
  return RC::SUCCESS;
}
int FloatType::cast_cost(AttrType type)
{
  if(type == AttrType::INTS){
    return 1;
  }
  else if(type == AttrType::FLOATS){
    return 0;
  }
  return INT32_MAX;
  
}

RC FloatType::cast_to(const Value&val, AttrType type , Value &result) const
{
  //LOG_INFO("float::Casting..");
  switch (type)
  {
  case AttrType::INTS:{
    result.set_int(val.get_float());
    break;
  }
  case AttrType::CHARS:{
    string str;
    RC rc = to_string(val, str);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    result.set_string(str.c_str());
  }
    break;
  default:
  return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}