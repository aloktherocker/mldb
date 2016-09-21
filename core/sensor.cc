/* sensor.cc
   Jeremy Barnes, 21 January 2014
   Copyright (c) 2014 Datacratic Inc.  All rights reserved.

   This file is part of MLDB. Copyright 2015 Datacratic. All rights reserved.

   Sensor support.
*/

#include "mldb/core/sensor.h"
#include "mldb/server/sensor_collection.h"
#include "mldb/server/mldb_server.h"
#include "mldb/server/static_content_handler.h"
#include "mldb/types/basic_value_descriptions.h"
#include "mldb/types/any_impl.h"

namespace Datacratic {
namespace MLDB {


/*****************************************************************************/
/* SENSOR                                                                    */
/*****************************************************************************/

Sensor::
Sensor(MldbServer * server)
    : server(static_cast<MldbServer *>(server))
{
}

Sensor::
~Sensor()
{
}

Any
Sensor::
getStatus() const
{
    return Any();
}
    
Any
Sensor::
getVersion() const
{
    return Any();
}

RestRequestMatchResult
Sensor::
handleRequest(RestConnection & connection,
              const RestRequest & request,
              RestRequestParsingContext & context) const
{
    Json::Value error;
    error["error"] = "Sensor of type '" + ML::type_name(*this)
        + "' does not respond to custom route '" + context.remaining + "'";
    error["details"]["verb"] = request.verb;
    error["details"]["resource"] = request.resource;
    connection.sendErrorResponse(400, error);
    return RestRequestRouter::MR_ERROR;
}

RestRequestMatchResult
Sensor::
handleDocumentationRoute(RestConnection & connection,
                         const RestRequest & request,
                         RestRequestParsingContext & context) const
{
    return RestRequestRouter::MR_NO;
}

RestRequestMatchResult
Sensor::
handleStaticRoute(RestConnection & connection,
                  const RestRequest & request,
                  RestRequestParsingContext & context) const
{
    return RestRequestRouter::MR_NO;
}

} // namespace MLDB
} // namespace Datacratic