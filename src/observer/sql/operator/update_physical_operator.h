#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, const std::unordered_map<std::string, std::shared_ptr<Expression>> &kv_pairs)
    : table_(table), kv_pairs_(kv_pairs) {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  RC set_value_to_record(char *record_data, const Value &value, const FieldMeta *field);
  RC set_value_from_record(const char *record_data, const FieldMeta *field, Value &value);

private:
  Table                                                        *table_ = nullptr;
  std::unordered_map<std::string, std::shared_ptr<Expression>>  kv_pairs_;
  Trx                                                          *trx_ = nullptr;
  std::vector<Record>                                           records_;
};
