/**
 * Namf_Communication
 * AMF Communication Service © 2019, 3GPP Organizational Partners (ARIB, ATIS,
 * CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.1.0.alpha-1
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "SubscriptionsCollectionDocumentApi.h"
#include "Helpers.h"
#include "amf_config.hpp"

extern config::amf_config amf_cfg;

namespace oai {
namespace amf {
namespace api {

using namespace oai::amf::helpers;
using namespace oai::amf::model;

SubscriptionsCollectionDocumentApi::SubscriptionsCollectionDocumentApi(
    std::shared_ptr<Pistache::Rest::Router> rtr) {
  router = rtr;
}

void SubscriptionsCollectionDocumentApi::init() {
  setupRoutes();
}

void SubscriptionsCollectionDocumentApi::setupRoutes() {
  using namespace Pistache::Rest;

  Routes::Post(
      *router, base + amf_cfg.sbi_api_version + "/subscriptions",
      Routes::bind(
          &SubscriptionsCollectionDocumentApi::
              a_mf_status_change_subscribe_handler,
          this));

  // Default handler, called when a route is not found
  router->addCustomHandler(Routes::bind(
      &SubscriptionsCollectionDocumentApi::
          subscriptions_collection_document_api_default_handler,
      this));
}

void SubscriptionsCollectionDocumentApi::a_mf_status_change_subscribe_handler(
    const Pistache::Rest::Request& request,
    Pistache::Http::ResponseWriter response) {
  // Getting the body param

  SubscriptionData subscriptionData;

  try {
    nlohmann::json::parse(request.body()).get_to(subscriptionData);
    this->a_mf_status_change_subscribe(subscriptionData, response);
  } catch (nlohmann::detail::exception& e) {
    // send a 400 error
    response.send(Pistache::Http::Code::Bad_Request, e.what());
    return;
  } catch (std::exception& e) {
    // send a 500 error
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
    return;
  }
}

void SubscriptionsCollectionDocumentApi::
    subscriptions_collection_document_api_default_handler(
        const Pistache::Rest::Request&,
        Pistache::Http::ResponseWriter response) {
  response.send(
      Pistache::Http::Code::Not_Found, "The requested method does not exist");
}

}  // namespace api
}  // namespace amf
}  // namespace oai
