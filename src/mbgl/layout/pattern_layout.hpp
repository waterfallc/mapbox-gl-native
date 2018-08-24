#pragma once
#include <mbgl/renderer/buckets/line_bucket.hpp>
#include <mbgl/renderer/bucket_parameters.hpp>
#include <mbgl/style/layers/line_layer_impl.hpp>

namespace mbgl {
  class LineBucket;

class PatternLayout {
public:
    PatternLayout(const BucketParameters&,
                  const std::vector<const RenderLayer*>&,
                  std::unique_ptr<GeometryTileLayer>,
                  ImageDependencies&);

    std::unique_ptr<LineBucket> createLayout(const ImagePositions&);
    std::map<std::string, RenderLinePaintProperties::PossiblyEvaluated> layerPaintProperties;

    const std::string bucketLeaderID;
private:
    const std::unique_ptr<GeometryTileLayer> sourceLayer;
    std::vector<std::unique_ptr<GeometryTileFeature>> features;
    style::LineLayoutProperties::PossiblyEvaluated layout;

    const float zoom;
    const uint32_t overscaling;
};
} // namespace mbgl

