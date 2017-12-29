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
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
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

#include <iostream>

#include <iota/constants.hpp>
#include <iota/errors/bad_request.hpp>
#include <iota/errors/internal_server_error.hpp>
#include <iota/errors/unauthorized.hpp>
#include <iota/errors/unrecognized.hpp>

#include <cpr/cpr.h>
#include <json.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

class Service {
public:
  Service(const std::string& host, const uint16_t& port);
  virtual ~Service();

public:
  template <typename Request, typename Response, typename... Args>
  Response request(Args&&... args) const {
    auto request = Request(args...);

    json data;
    request.serialize(data);

    auto url     = cpr::Url{ "http://" + host_ + ":" + std::to_string(port_) };
    auto body    = cpr::Body{ data.dump() };
    auto headers = cpr::Header{ { "Content-Type", "application/json" },
                                { "Content-Length", std::to_string(body.size()) },
                                { "X-IOTA-API-Version", APIVersion } };
    auto res     = cpr::Post(url, body, headers);

    Response response;
    // TODO set duration ?
    if (res.status_code == 200)
      response.deserialize(json::parse(res.text));
    else if (res.status_code == 400)
      throw Errors::BadRequest(json::parse(res.text)["error"].get<std::string>());
    else if (res.status_code == 401)
      throw Errors::Unauthorized(json::parse(res.text)["error"].get<std::string>());
    else if (res.status_code == 500)
      throw Errors::InternalServerError(json::parse(res.text)["error"].get<std::string>());
    else
      throw Errors::Unrecognized(json::parse(res.text)["error"].get<std::string>());

    return response;
  }

private:
  std::string  host_;
  unsigned int port_;
};

}  // namespace API

}  // namespace IOTA
