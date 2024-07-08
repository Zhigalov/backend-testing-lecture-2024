#include "calculate.hpp"

#include <string>

#include <userver/clients/http/component.hpp>
#include <userver/components/component.hpp>
#include <userver/formats/json.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/utest/using_namespace_userver.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

#include "../example_02/pluralize.hpp"

namespace testing_lecture::example_03 {

namespace {

using namespace formats::json;

std::string BuildDeliveryBody(const userver::server::http::HttpRequest& request) {
  ValueBuilder body;
  body["payment_info"] = ValueBuilder(formats::common::Type::kObject)
                            .ExtractValue();

  ValueBuilder item;
  item["quantity"] = 1;
  body["items"].PushBack(std::move(item));

  ValueBuilder source_point;
  source_point["lat"] = std::stod(request.GetArg("a_lat"));
  source_point["lon"] = std::stod(request.GetArg("a_lon"));
  body["route_points"].PushBack(std::move(source_point));

  ValueBuilder destination_point;
  destination_point["lat"] = std::stod(request.GetArg("b_lat"));
  destination_point["lon"] = std::stod(request.GetArg("b_lon"));
  body["route_points"].PushBack(std::move(destination_point));

  return ToStableString(body.ExtractValue());
}

std::string MakeDeliveryRequest(clients::http::Client& client,
                                const std::string& url,
                                const std::string& body) {
  const auto response = client
    .CreateRequest()
    .post(url, body)
    .headers({
      {"accept-language", "ru"},
      {"content-type", "application/json"},
    })
    .timeout(std::chrono::milliseconds{500})
    .perform();
  response->raise_for_status();

  return std::string{response->body_view()};
}

std::string ParsePrice(const std::string& response) {
  const auto json = FromString(response);
  if (!json.HasMember("claims_offers") ||
      !json["claims_offers"].IsArray() ||
      json["claims_offers"].IsEmpty() ||
      !json["claims_offers"][0].HasMember("price") ||
      !json["claims_offers"][0]["price"].HasMember("total_price")) {
    return std::string{"Ошибка получения цены"};
  }

  return json["claims_offers"][0]["price"]["total_price"]
    .As<std::string>();
}

class Calculate final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-calculate";

  Calculate(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context)
      , http_client_(
          component_context.FindComponent<components::HttpClient>().GetHttpClient())
      , url_(config["delivery-url"].As<std::string>()) {}

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    const auto body = BuildDeliveryBody(request);
    const auto response = MakeDeliveryRequest(
      http_client_, url_, body
    );
    const auto price = ParsePrice(response);
    const auto plural = example_02::pluralize(
      std::stoi(price),
      {"рубль", "рубля", "рублей"}
    );

    return price + " " + plural;
  }

  static yaml_config::Schema GetStaticConfigSchema() {
    return yaml_config::MergeSchemas<userver::server::handlers::HttpHandlerBase>(R"(
type: object
description: HTTP  sample component
additionalProperties: false
properties:
    delivery-url:
        type: string
        description: some other microservice listens on this URL
)");
  }
 private:
  clients::http::Client& http_client_;
  const std::string url_;
};

}  // namespace

void AppendCalculate(userver::components::ComponentList& component_list) {
  component_list.Append<Calculate>();
}

/**
curl 'https://dostavka.yandex.ru/api/b2b/external/phoenix/dcaa/cargo/v2/offers/calculate?country=rus' \
  -H 'accept-language: ru' \
  -H 'content-type: application/json' \
  --data-raw '{"payment_info":{},"items":[{"quantity":1}],"route_points":[{"lon":60.62944549875555,"lat":56.84342722610512},{"lon":60.59110540242933,"lat":56.83548550031163}]}' | jq .
*/

/**
curl 'http://localhost:8080/v1/calculate?a_lat=56.843427&a_lon=60.629445&b_lat=56.835485&b_lon=60.591105' -d ''
*/

}  // namespace testing_lecture::example_03