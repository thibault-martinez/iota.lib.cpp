//
// MIT License
//
// Copyright (c) 2017 Thibault Martinez
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

#include <iota/api/responses/base.hpp>
#include <iota/models/transaction.hpp>

namespace IOTA {

namespace API {

namespace Responses {

class GetBundle : public Base {
public:
  /**
   * default ctor
   */
  GetBundle() = default;

  /**
   * full init ctor
   *
   * @param transactions transactions returned by GetBundle
   * @param duration duration of GetBundle
   */
  GetBundle(const std::vector<Models::Transaction>& transactions, const int64_t& duration);

  /**
   * default dtor
   */
  ~GetBundle() = default;

public:
  /**
   * @return The transactions.
   */
  const std::vector<Models::Transaction>& getTransactions() const;

  /**
   * @return The transactions (Non-const version).
   */
  std::vector<Models::Transaction>& getTransactions();

  /**
   * @param transactions new transactions list for GetBundle
   */
  void setTransactions(const std::vector<Models::Transaction>& transactions);

private:
  std::vector<Models::Transaction> transactions_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
