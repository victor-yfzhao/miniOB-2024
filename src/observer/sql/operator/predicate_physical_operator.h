/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/6/27.
//

#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"

class FilterStmt;

/**
 * @brief 过滤/谓词物理算子
 * @ingroup PhysicalOperator
 */
class PredicatePhysicalOperator : public PhysicalOperator
{
public:
  PredicatePhysicalOperator(std::unique_ptr<Expression> expr);

  virtual ~PredicatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::PREDICATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  RC tuple_schema(TupleSchema &schema) const override;

private:
  std::unique_ptr<Expression> expression_;
  int sub_selection_result_index_ = 0; 
  int sub_selection_result_size_ = 0;
  int has_sub_select_ = 0;
  Trx *trx_ = nullptr;
  SubSelectExpr *left_sub_select_expr_ = nullptr;
  SubSelectExpr *right_sub_select_expr_ = nullptr;
};
