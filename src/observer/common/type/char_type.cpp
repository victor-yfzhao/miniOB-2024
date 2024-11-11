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
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"

#include <regex.h>
#include <stdbool.h>

int CharType::compare(const Value &left, const Value &right) const
{
  if (left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS) {
    return INT32_MAX;
  }

  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

bool CharType::like(const Value &left, const Value &right) const
{
  if(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS) {
    return false;
  }

  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");

  const char *str = left.value_.pointer_value_;
  const char *like_str = right.value_.pointer_value_;

    char regex_pattern[1024] = "^";  // 起始字符
    size_t len = right.length_;
    
    // 遍历 like_str 并将通配符转换为正则表达式
    for (size_t i = 0; i < len; ++i) {
        char c = like_str[i];
        if (c == '%') {
            // % 替换为 .*
            strcat(regex_pattern, ".*");
        } else if (c == '_') {
            // _ 替换为 .
            strcat(regex_pattern, ".");
        } else {
            // 如果是正则表达式的特殊字符，则进行转义
            if (strchr(".^$|(){}+?*\\", c)) {
                strcat(regex_pattern, "\\");
            }
            // 直接将字符追加到正则表达式模式中
            strncat(regex_pattern, &c, 1);
        }
    }

    // 添加结束符 $
    strcat(regex_pattern, "$");

    // 编译正则表达式
    regex_t regex;
    int reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    // 执行正则匹配
    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    // 返回匹配结果
    return !reti; // 0 表示匹配成功，非0表示失败

}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::DATES: {
      return DataType::type_instance(AttrType::DATES)->set_value_from_str(result, val.get_string());
    }
      break;
    case AttrType::VECTORS: {
      return DataType::type_instance(AttrType::VECTORS)->set_value_from_str(result, val.get_string());
      }
      break; 
    case AttrType::INTS: {
      return DataType::type_instance(AttrType::INTS)->set_value_from_str(result,val.get_string());
    } 
      break;
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  if (type == AttrType::CHARS) {
    return 0;
  }
  if (type == AttrType::DATES) {
    return 1;
  }
  if (type == AttrType::VECTORS) {
    return 0;
  }
  if( type == AttrType::INTS)
  {
    return 2;
  }
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}