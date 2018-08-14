#pragma once

#include <mbgl/style/expression/expression.hpp>
#include <mbgl/style/expression/parsing_context.hpp>
#include <mbgl/style/conversion.hpp>

#include <memory>

namespace mbgl {
namespace style {
namespace expression {
    
class FormatExpression : public Expression {
public:
    FormatExpression(std::unique_ptr<Expression> text,
                     optional<std::unique_ptr<Expression>> fontScale,
                     optional<std::unique_ptr<Expression>> textFont);
    
    EvaluationResult evaluate(const EvaluationContext&) const override;
    static ParseResult parse(const mbgl::style::conversion::Convertible&, ParsingContext&);
    
    void eachChild(const std::function<void(const Expression&)>&) const override;
    
    bool operator==(const Expression& e) const override;
    
    std::vector<optional<Value>> possibleOutputs() const override {
        // Technically the combinatoric set of all children
        // Usually, this.text will be undefined anyway
        return { nullopt };
    }
    
    mbgl::Value serialize() const override;
    std::string getOperator() const override { return "format"; }
private:
    std::unique_ptr<Expression> text;
    optional<std::unique_ptr<Expression>> fontScale;
    optional<std::unique_ptr<Expression>> textFont;
};
    
} // namespace expression
} // namespace style
} // namespace mbgl
