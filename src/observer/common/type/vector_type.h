/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/rc.h"
#include "common/type/data_type.h"

/**
 * @brief 向量类型
 * @ingroup DataType
 */
class VectorType : public DataType
{
public:
  VectorType() : DataType(AttrType::VECTORS) {}
  virtual ~VectorType() {}

  int compare(const Value &left, const Value &right) const override;

  RC add(const Value &left, const Value &right, Value &result) const override;
  RC subtract(const Value &left, const Value &right, Value &result) const override;
  RC multiply(const Value &left, const Value &right, Value &result) const override;
  RC prepare_vectors(const Value &left, const Value &right, std::vector<double> &left_vector, std::vector<double> &right_vector) const override;
  RC set_value_from_str(Value &val, const string &data) const override;

  RC L2_DISTANCE(const Value &left, const Value &right, Value &result) const override;
  RC COSINE_DISTANCE(const Value &left, const Value &right, Value &result) const override;
  RC INNER_PRODUCT(const Value &left, const Value &right, Value &result) const override;
  RC to_string(const Value &val, string &result) const override;
};