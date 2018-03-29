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

#pragma once

#include <functional>
#include <string>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace IOTA {

namespace Utils {

/**
 * json 3rd party library wrapper
 * hides some internal mechanisms related to the json library
 * also makes it easier to switch from one libary to another in the future
 */
class json {
public:
  /**
   * Default ctor
   */
  json(void);

  /**
   * Default dtor
   */
  ~json(void) = default;

  /**
   * Move constructor
   */
  json(json&&) = default;

  /**
   * Move operator
   */
  json& operator=(json&&) = default;

  /**
   * Disabled copy constructor to ensure memory efficiency
   */
  json(const json&) = delete;

  /**
   * Disabled assignment operator to ensure memory efficiency
   */
  json& operator=(const json&) = delete;

private:
  /**
   * ctor from json value
   * move the json value
   */
  json(const rapidjson::Value& val);

public:
  /**
   * parse the given json string and loads the content in the current object
   * @param json_str  the json string to be parsed
   */
  void loads(const std::string& json_str);

  /**
   * convert the json object into a json string
   * @return the converted json string
   */
  std::string dumps(void) const;

public:
  /**
   * check key existence in json object
   * @param the key to check
   * @return whether the object contains the given key
   */
  bool has(const std::string& key) const;

public:
  /**
   * set the key with the integer value
   * @param key    the key to be set
   * @param value  the value to set the key with
   */
  void set(const std::string& key, int64_t value);

  /**
   * set the key with the string value
   * @param key   the key to be set
   * @param value  the value to set the key with
   */
  void set(const std::string& key, const std::string& value);

  /**
   * set the key with the string array value
   * @param key    the key to be set
   * @param value  the value to set the key with
   */
  void set(const std::string& key, const std::vector<std::string>& value);

  /**
   * set the key with the string array value
   * takes as input an array of any model and a function converting each item into a string
   * @param key        the key to be set
   * @param value      the value to set the key with
   * @param converter  function called on each item of value to convert them to string
   */
  template <typename T>
  void set(const std::string& key, const std::vector<T>& value,
           const std::function<std::string(const T&)>& converter) {
    auto arr     = rapidjson::Value{ rapidjson::kArrayType };
    auto key_val = rapidjson::Value{ key.data(), memory_pool_ };

    for (const auto& val : value) {
      arr.PushBack(rapidjson::Value(converter(val).data(), memory_pool_).Move(), memory_pool_);
    }

    json_.AddMember(key_val.Move(), arr.Move(), memory_pool_);
  }

public:
  /**
   * get an integer value for the given key
   * assumption is made that key exists (this function will **not** check for existence)
   * @param key  the key to retrieve
   * @return the retrieved value
   */
  int64_t getInt(const std::string& key) const;

  /**
   * get a string value for the given key
   * assumption is made that key exists (this function will **not** check for existence)
   * @param key  the key to retrieve
   * @return the retrieved value
   */
  std::string getString(const std::string& key) const;

  /**
   * get a string vector value for the given key
   * assumption is made that key exists (this function will **not** check for existence)
   * @param key  the key to retrieve
   * @return the retrieved value
   */
  std::vector<std::string> getStringVector(const std::string& key) const;

  /**
   * get a boolean vector value for the given key
   * assumption is made that key exists (this function will **not** check for existence)
   * @param key  the key to retrieve
   * @return the retrieved value
   */
  std::vector<bool> getBoolVector(const std::string& key) const;

  /**
   * get a json vector value for the given key
   * assumption is made that key exists (this function will **not** check for existence)
   * @param key  the key to retrieve
   * @return the retrieved value
   */
  std::vector<json> getJsonVector(const std::string& key) const;

private:
  /**
   * json memory pool, shared among all json objects
   */
  static rapidjson::MemoryPoolAllocator<> memory_pool_;

private:
  /**
   * the json object itself
   */
  rapidjson::Document json_;
};

}  // namespace Utils

}  // namespace IOTA
