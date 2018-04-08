//
// MIT License
//
// Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#include <iota/utils/json.hpp>

namespace IOTA {

namespace Utils {

rapidjson::MemoryPoolAllocator<> json::memory_pool_;

json::json(void) : json_(rapidjson::kObjectType, &memory_pool_) {
}

json::json(const rapidjson::Value& val) : json_(rapidjson::kObjectType, &memory_pool_) {
  json_.CopyFrom(val, memory_pool_);
}

void
json::loads(const std::string& json_str) {
  json_.Parse(json_str.c_str());
}

std::string
json::dumps(void) const {
  rapidjson::StringBuffer                    buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  json_.Accept(writer);

  return buffer.GetString();
}

bool
json::has(const std::string& key) const {
  return json_.HasMember(key.data());
}

void
json::set(const std::string& key, int64_t value) {
  auto key_val = rapidjson::Value{ key.data(), memory_pool_ };

  json_.AddMember(key_val.Move(), value, memory_pool_);
}

void
json::set(const std::string& key, const std::string& value) {
  auto val     = rapidjson::Value(value.data(), memory_pool_);
  auto key_val = rapidjson::Value{ key.data(), memory_pool_ };

  json_.AddMember(key_val.Move(), val.Move(), memory_pool_);
}

void
json::set(const std::string& key, const std::vector<std::string>& value) {
  auto arr     = rapidjson::Value{ rapidjson::kArrayType };
  auto key_val = rapidjson::Value{ key.data(), memory_pool_ };

  for (const auto& val : value) {
    arr.PushBack(rapidjson::Value(val.data(), memory_pool_).Move(), memory_pool_);
  }

  json_.AddMember(key_val.Move(), arr.Move(), memory_pool_);
}

void
json::set(const std::string& key, const std::vector<bool>& value) {
  auto arr     = rapidjson::Value{ rapidjson::kArrayType };
  auto key_val = rapidjson::Value{ key.data(), memory_pool_ };

  for (const auto& val : value) {
    arr.PushBack(val, memory_pool_);
  }

  json_.AddMember(key_val.Move(), arr.Move(), memory_pool_);
}

void
json::set(const std::string& key, std::vector<json>& value) {
  auto arr     = rapidjson::Value{ rapidjson::kArrayType };
  auto key_val = rapidjson::Value{ key.data(), memory_pool_ };

  for (auto& val : value) {
    arr.PushBack(val.json_, memory_pool_);
  }

  json_.AddMember(key_val.Move(), arr.Move(), memory_pool_);
}

int64_t
json::getInt(const std::string& key) const {
  return json_[key.data()].GetInt64();
}

std::string
json::getString(const std::string& key) const {
  return json_[key.data()].GetString();
}

std::vector<std::string>
json::getStringVector(const std::string& key) const {
  auto arr = json_[key.data()].GetArray();

  std::vector<std::string> res;
  for (auto it = arr.Begin(); it != arr.End(); ++it) {
    res.push_back(it->GetString());
  }

  return res;
}

std::vector<bool>
json::getBoolVector(const std::string& key) const {
  auto arr = json_[key.data()].GetArray();

  std::vector<bool> res;
  for (auto it = arr.Begin(); it != arr.End(); ++it) {
    res.push_back(it->GetBool());
  }

  return res;
}

std::vector<json>
json::getJsonVector(const std::string& key) const {
  auto arr = json_[key.data()].GetArray();

  std::vector<json> res;
  for (auto it = arr.Begin(); it != arr.End(); ++it) {
    res.push_back(json(*it));
  }

  return res;
}

}  // namespace Utils

}  // namespace IOTA
