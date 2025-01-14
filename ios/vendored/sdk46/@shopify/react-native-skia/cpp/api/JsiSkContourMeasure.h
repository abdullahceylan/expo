#pragma once

#include <memory>
#include <utility>

#include <ABI46_0_0jsi/ABI46_0_0jsi.h>

#include "JsiSkHostObjects.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <SkContourMeasure.h>

#pragma clang diagnostic pop


namespace ABI46_0_0RNSkia
{

    using namespace ABI46_0_0facebook;

    class JsiSkContourMeasure : public JsiSkWrappingSkPtrHostObject<SkContourMeasure>
    {
    public:
        JsiSkContourMeasure(std::shared_ptr<ABI46_0_0RNSkPlatformContext> context,
                            const sk_sp<SkContourMeasure> contourMeasure)
            : JsiSkWrappingSkPtrHostObject(std::move(context), std::move(contourMeasure))
        {
            if (contourMeasure == nullptr)
            {
                jsi::detail::throwJSError(*context->getJsRuntime(), "Contour measure is null");
            }
        };

        JSI_HOST_FUNCTION(getPosTan)
        {
            auto dist = arguments[0].asNumber();
            SkPoint position;
            SkPoint tangent;
            auto result = getObject()->getPosTan(dist, &position, &tangent);
            if (!result)
            {
                jsi::detail::throwJSError(runtime, "getSegment() failed");
            }
            auto posTan = jsi::Object(runtime);
            posTan.setProperty(runtime, "px", position.x());
            posTan.setProperty(runtime, "py", position.y());
            posTan.setProperty(runtime, "tx", tangent.x());
            posTan.setProperty(runtime, "ty", tangent.y());
            return posTan;
        }

        JSI_HOST_FUNCTION(length)
        {
            return jsi::Value(SkScalarToDouble(getObject()->length()));
        }

        JSI_HOST_FUNCTION(isClosed)
        {
            return jsi::Value(getObject()->isClosed());
        }

        JSI_HOST_FUNCTION(getSegment)
        {
            auto start = arguments[0].asNumber();
            auto end = arguments[1].asNumber();
            auto startWithMoveTo = arguments[2].getBool();
            SkPath path;
            auto result = getObject()->getSegment(start, end, &path, startWithMoveTo);
            if (!result)
            {
                jsi::detail::throwJSError(runtime, "getSegment() failed");
            }
            return JsiSkPath::toValue(runtime, getContext(), std::move(path));
        }

        JSI_PROPERTY_GET(__typename__)
        {
            return jsi::String::createFromUtf8(runtime, "ContourMeasure");
        }

        JSI_EXPORT_PROPERTY_GETTERS(JSI_EXPORT_PROP_GET(JsiSkContourMeasure, __typename__))

        JSI_EXPORT_FUNCTIONS(
            JSI_EXPORT_FUNC(JsiSkContourMeasure, getPosTan),
            JSI_EXPORT_FUNC(JsiSkContourMeasure, length),
            JSI_EXPORT_FUNC(JsiSkContourMeasure, isClosed),
            JSI_EXPORT_FUNC(JsiSkContourMeasure, getSegment))

        /**
          Returns the underlying object from a host object of this type
         */
        static sk_sp<SkContourMeasure> fromValue(jsi::Runtime &runtime,
                                                 const jsi::Value &obj)
        {
            return obj.asObject(runtime)
                .asHostObject<JsiSkContourMeasure>(runtime)
                ->getObject();
        }
    };
} // namespace ABI46_0_0RNSkia