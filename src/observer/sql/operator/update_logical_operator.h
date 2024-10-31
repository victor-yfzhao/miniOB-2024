#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const std::unordered_map<std::string, const Value *> &kv_pairs)
      : table_(table), kv_pairs_(kv_pairs) {};
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  Table              *table() const { return table_; }
  const std::unordered_map<std::string, const Value *> &kv_pairs() const { return kv_pairs_; }
  // FilterLogicalOperator *filter_op() const { return filter_op_; }

private:
  Table                                               *table_ = nullptr;
  const std::unordered_map<std::string, const Value *> kv_pairs_;
  // FilterLogicalOperator *filter_op_ = nullptr;
};
    