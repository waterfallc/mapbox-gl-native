#pragma once

#include <mbgl/util/optional.hpp>

#include <vector>
#include <string>

namespace mbgl {
namespace style {
namespace expression {

struct FormattedSection {
    FormattedSection(std::string text_, optional<double> fontScale_, optional<std::string> fontStack_)
        : text(std::move(text_))
        , fontScale(std::move(fontScale_))
        , fontStack(std::move(fontStack_))
    {}
    std::string text;
    optional<double> fontScale;
    optional<std::string> fontStack;
};

class Formatted {
public:
    Formatted(std::vector<FormattedSection> sections_)
        : sections(std::move(sections_))
    {}
    
    bool operator==(const Formatted& ) const {
        return false; // TODO
    }
private:
    std::vector<FormattedSection> sections;
};
            
} // namespace expression
} // namespace style
} // namespace mbgl
