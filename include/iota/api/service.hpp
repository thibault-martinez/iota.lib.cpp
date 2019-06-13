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

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <nlohmann/json.hpp>

#include <iota/constants.hpp>
#include <iota/errors/bad_request.hpp>
#include <iota/errors/internal_server_error.hpp>
#include <iota/errors/network.hpp>
#include <iota/errors/unauthorized.hpp>
#include <iota/errors/unrecognized.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

/**
 * Service to contact a IOTA node.
 */
class Service {
public:
  /**
   * Full init ctor.
   *
   * @param host Host of the node.
   * @param port Port of the node.
   * @param timeout Request timeout.
   */
  Service(const std::string& host, const uint16_t& port, int timeout = 60,
          const std::string& user = "", const std::string& pass = "");
  /**
   * Default dtor;
   */
  virtual ~Service() = default;

public:
  /**
   * Request to the node.
   *
   * @param args The request parameters.
   *
   * @return The request response.
   */
  template <typename Request, typename Response, typename... Args>
  Response request(Args&&... args) const {
    auto request = Request{ args... };

    json data, result;
    request.serialize(data);

    using tcp      = boost::asio::ip::tcp;
    namespace http = boost::beast::http;

    boost::asio::io_context   ioc;
    boost::system::error_code ec;
    tcp::resolver             resolver{ ioc };
    tcp::socket               socket{ ioc };

    try {
      auto const results = resolver.resolve(host_, std::to_string(port_));

      boost::asio::connect(socket, results.begin(), results.end());

      http::request<http::string_body> req{ http::verb::post, "/", 11 };
      req.set(http::field::host, host_);
      req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
      req.set(http::field::content_type, "application/json");
      req.set("X-IOTA-API-Version", "1");
      req.body() = data.dump();
      req.content_length(req.body().size());

      http::write(socket, req);
      boost::beast::flat_buffer         buffer;
      http::response<http::string_body> res;

      http::read(socket, buffer, res);
      result = json::parse(res.body());

      socket.shutdown(tcp::socket::shutdown_both, ec);

      if (ec && ec != boost::system::errc::not_connected)
        throw boost::system::system_error{ ec };
    } catch (const std::exception& ex) {
      throw Errors::Unrecognized(std::string("Invalid reply from node: ") + ex.what());
    }

    return Response{ result };
  }

private:
  /**
   * Host of the node.
   */
  std::string host_;
  /**
   * Port of the node.
   */
  unsigned int port_;
  /**
   * Timeout for requests.
   */
  const int timeout_;
  /**
   * Username for authenticated requests.
   */
  std::string user_;
  /**
   * Password for authenticated requests.
   */
  std::string pass_;
};

}  // namespace API

}  // namespace IOTA
