#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/vector_type.h"
#include "common/value.h"
#include <sstream>
#include <cmath>

int VectorType::compare(const Value &left, const Value &right) const
{
  ASSERT(!(left.attr_type() != AttrType::VECTORS && right.attr_type() != AttrType::VECTORS), "invalid type");

  std::vector<float> left_vector;
  std::vector<float> right_vector;

  RC rc = prepare_vectors(left, right, left_vector, right_vector);
  if (rc != RC::SUCCESS) {
    LOG_WARN("Failed to prepare vectors. rc=%d", rc);
    return INT32_MAX;
  }

  size_t min_size = std::min(left_vector.size(), right_vector.size());
  for (size_t i = 0; i < min_size; ++i) {
    if (left_vector[i] < right_vector[i]) {
      return -1;
    } else if (left_vector[i] > right_vector[i]) {
      return 1;
    }
  }

  if (left_vector.size() < right_vector.size()) {
    return INT32_MAX;
  } else if (left_vector.size() > right_vector.size()) {
    return INT32_MAX;
  }

  return 0;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> left_vector;
  std::vector<float> right_vector;

  RC rc = prepare_vectors(left, right, left_vector, right_vector);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  result.set_vector(new std::vector<float>(left_vector.size()));
  for (size_t i = 0; i < left_vector.size(); ++i) {
    result.get_vector()->at(i) = left_vector[i] + right_vector[i];
  }

  return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> left_vector;
  std::vector<float> right_vector;

  RC rc = prepare_vectors(left, right, left_vector, right_vector);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  result.set_vector(new std::vector<float>(left_vector.size()));
  for (size_t i = 0; i < left_vector.size(); ++i) {
    result.get_vector()->at(i) = left_vector[i] - right_vector[i];
  }

  return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> left_vector;
  std::vector<float> right_vector;

  RC rc = prepare_vectors(left, right, left_vector, right_vector);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  result.set_vector(new std::vector<float>(left_vector.size()));
  for (size_t i = 0; i < left_vector.size(); ++i) {
    result.get_vector()->at(i) = left_vector[i] * right_vector[i];
  }

  return RC::SUCCESS;
}

RC VectorType::prepare_vectors(const Value &left, const Value &right, std::vector<float> &left_vector, std::vector<float> &right_vector) const
{
  ASSERT(left.attr_type() == AttrType::VECTORS || left.attr_type() == AttrType::CHARS, "invalid type");
  ASSERT(right.attr_type() == AttrType::VECTORS || right.attr_type() == AttrType::CHARS, "invalid type");

  if (left.attr_type() == AttrType::CHARS) {
    Value tmp;
    RC rc = set_value_from_str(tmp, left.get_string());
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to set value from string for left vector. rc=%d", rc);
      return rc;
    }
    left_vector = *tmp.get_vector();
  } else {
    left_vector = *left.get_vector();
  }

  if (right.attr_type() == AttrType::CHARS) {
    Value tmp;
    RC rc = set_value_from_str(tmp, right.get_string());
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to set value from string for right vector. rc=%d", rc);
      return rc;
    }
    right_vector = *tmp.get_vector();
  } else {
    right_vector = *right.get_vector();
  }

  if (left_vector.size() != right_vector.size()) {
    return RC::INVALID_ARGUMENT;
  }

  return RC::SUCCESS;
}

RC VectorType::set_value_from_str(Value &val, const std::string &data) const
{
  size_t first_embrace = data.find_first_of('[');
  size_t second_embrace = data.find_first_of(']', first_embrace + 1);

  if (first_embrace == std::string::npos || second_embrace == std::string::npos) {
    return RC::INVALID_ARGUMENT;
  }
  if (second_embrace <= first_embrace + 1) {
    return RC::INVALID_ARGUMENT;
  }

  std::string vector_data = data.substr(first_embrace + 1, second_embrace - first_embrace - 1);
  std::stringstream ss(vector_data);
  std::string item;
  std::vector<float> *vec = new std::vector<float>();

  while (std::getline(ss, item, ',')) {
    try {
      vec->push_back(std::stod(item));
    } catch (const std::exception& e) {
      delete vec;
      return RC::INVALID_ARGUMENT;
    }
  }

  // 这里假设 val 是一个可以存储 vector<float>* 的类型
  val.set_vector(vec);

  return RC::SUCCESS;
}
RC VectorType::to_string(const Value &val, string &result) const
{
   const std::vector<float> *vec = val.get_vector();
  if (vec == nullptr || vec->empty()) {
    result = "[]";
    return RC::INVALID_ARGUMENT;
  }

  // 计算所需的缓冲区大小
  size_t buffer_size = vec->size() * 15 + 2; // 每个整数最多 11 位，加上逗号和空格
  char *buffer = new char[buffer_size];
  char *ptr = buffer;

  ptr += snprintf(ptr, buffer_size, "[");
for (size_t i = 0; i < vec->size(); ++i) {
  if (i > 0) {
    ptr += snprintf(ptr, buffer_size - (ptr - buffer), ",");
  }
  char temp[20];
  snprintf(temp, sizeof(temp), "%.2f", vec->at(i));

  // 删除尾随的零
  char *end = temp + strlen(temp) - 1;
  while (end > temp && *end == '0') {
    *end = '\0';
    end--;
  }
  if (end > temp && *end == '.') {
    *end = '\0';
  }

  ptr += snprintf(ptr, buffer_size - (ptr - buffer), "%s", temp);

  }
  snprintf(ptr, buffer_size - (ptr - buffer), "]");

  result = buffer;

  return RC::SUCCESS;
}

RC VectorType::L2_DISTANCE(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> left_vector;
  std::vector<float> right_vector;

  RC rc = prepare_vectors(left, right, left_vector, right_vector);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  float sum = 0;
  for (size_t i = 0; i < left_vector.size(); ++i) {
    sum += (left_vector[i] - right_vector[i]) * (left_vector[i] - right_vector[i]);
  }

  result.set_float(sqrt(sum));

  return RC::SUCCESS;
} 

RC VectorType::COSINE_DISTANCE(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> left_vector;
  std::vector<float> right_vector;

  RC rc = prepare_vectors(left, right, left_vector, right_vector);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  float dot_product = 0;
  float left_norm = 0;
  float right_norm = 0;
  for (size_t i = 0; i < left_vector.size(); ++i) {
    dot_product += left_vector[i] * right_vector[i];
    left_norm += left_vector[i] * left_vector[i];
    right_norm += right_vector[i] * right_vector[i];
  }
  float val = 1 - dot_product / (sqrt(left_norm) * sqrt(right_norm));
  if (val <= 0)
  {
     val = 0;
  }
  
  result.set_float(val);

  return RC::SUCCESS;
}

RC VectorType::INNER_PRODUCT(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> left_vector;
  std::vector<float> right_vector;

  RC rc = prepare_vectors(left, right, left_vector, right_vector);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  float sum = 0;
  for (size_t i = 0; i < left_vector.size(); ++i) {
    sum += left_vector[i] * right_vector[i];
  }

  result.set_float(sum);

  return RC::SUCCESS;
}