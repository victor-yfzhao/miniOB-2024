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

#include "sql/operator/predicate_physical_operator.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"
#include "storage/record/record.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == AttrType::BOOLEANS, "predicate's expression should be BOOLEAN type");
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  this->trx_ = trx;

  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  auto *expr = dynamic_cast<ConjunctionExpr *>(expression_.get());
  if (nullptr != expr) expr->set_trx(trx);
  for (auto &child : expr->children()) {
    if (child->type() == ExprType::COMPARISON) {
      ComparisonExpr *comp_expr = static_cast<ComparisonExpr *>(child.get());
      if (comp_expr->left()->type() == ExprType::SUB_SELECT) {
        SubSelectExpr *sub_select_expr = static_cast<SubSelectExpr *>(comp_expr->left().get());
        left_sub_select_expr_ = sub_select_expr;
        RC rc = sub_select_expr->set_sub_select_result();
        if (rc != RC::SUCCESS) {
          return rc;
        }
        auto values = sub_select_expr->sub_select_result();
        sub_selection_result_size_ = values.size();
        has_sub_select_ = 1;
      }
      if (comp_expr->right()->type() == ExprType::SUB_SELECT) {
        SubSelectExpr *sub_select_expr = static_cast<SubSelectExpr *>(comp_expr->right().get());
        right_sub_select_expr_ = sub_select_expr;
        if(sub_select_expr->sub_select_result().empty()){
          RC rc = sub_select_expr->set_sub_select_result();
          if (rc != RC::SUCCESS) {
            return rc;
          }
        }
        auto values = sub_select_expr->sub_select_result();
        sub_select_expr->set_sub_select_result();
        has_sub_select_ = (has_sub_select_ == 1) ? 3 : 2;
      }
    }
  }

  return children_[0]->open(trx);
}

RC PredicatePhysicalOperator::next()
{
  RC                rc   = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    Value value;
    rc = expression_->get_value(*tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }

  sub_selection_result_index_++;
  switch(has_sub_select_){
    case 1:{
      if (sub_selection_result_index_ < sub_selection_result_size_) {
        left_sub_select_expr_->set_index(sub_selection_result_index_);
        return RC::SUCCESS;
      }
    }break;
    case 2:{
      if (sub_selection_result_index_ < sub_selection_result_size_) {
        right_sub_select_expr_->set_index(sub_selection_result_index_);
        return RC::SUCCESS;
      }
    }break;
    case 3:{
      if (sub_selection_result_index_ < sub_selection_result_size_) {
        left_sub_select_expr_->set_index(sub_selection_result_index_);
        right_sub_select_expr_->set_index(sub_selection_result_index_);
        return RC::SUCCESS;
      }
    }break;
    default:break;
  }
  if (sub_selection_result_index_ < sub_selection_result_size_) {
    children_[0]->close();
    rc = children_[0]->open(trx_);
    return RC::SUCCESS;
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  // auto conj_expr = dynamic_cast<ConjunctionExpr *>(expression_.get());
  // for (auto &expr : conj_expr->children()) {
  //   if (expr->type() == ExprType::COMPARISON) {
  //     ComparisonExpr *comp_expr = static_cast<ComparisonExpr *>(expr.get());
  //     if (comp_expr->left()->type() == ExprType::SUB_SELECT) {
  //       SubSelectExpr *sub_select_expr = static_cast<SubSelectExpr *>(comp_expr->left().get());
  //       sub_select_expr->project_phy_oper()->close();
  //     }
  //     if (comp_expr->right()->type() == ExprType::SUB_SELECT) {
  //       SubSelectExpr *sub_select_expr = static_cast<SubSelectExpr *>(comp_expr->right().get());
  //       sub_select_expr->project_phy_oper()->close();
  //     }
  //   }
  // }

  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple() { return children_[0]->current_tuple(); }

RC PredicatePhysicalOperator::tuple_schema(TupleSchema &schema) const
{
  return children_[0]->tuple_schema(schema);
}
