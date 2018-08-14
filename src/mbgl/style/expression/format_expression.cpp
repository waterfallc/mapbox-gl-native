#include <mbgl/style/expression/formatted.hpp>
#include <mbgl/style/expression/format_expression.hpp>
#include <mbgl/style/expression/literal.hpp>
#include <mbgl/util/string.hpp>

namespace mbgl {
namespace style {
namespace expression {

FormatExpression::FormatExpression(std::unique_ptr<Expression> text_,
                                   optional<std::unique_ptr<Expression>> fontScale_,
                                   optional<std::unique_ptr<Expression>> textFont_)
: Expression(Kind::FormatExpression, type::Formatted)
, text(std::move(text_))
, fontScale(std::move(fontScale_))
, textFont(std::move(textFont_))
{}

using namespace mbgl::style::conversion;

ParseResult FormatExpression::parse(const Convertible& value, ParsingContext& ctx) {
    std::size_t argsLength = arrayLength(value);
    if (argsLength < 3) {
        ctx.error("Expected at least two arguments.");
        return ParseResult();
    }
    
    if ((argsLength - 1) % 2 != 0) {
        ctx.error("Expected an even number of arguments.");
        return ParseResult();
    }
    
    std::vector<FormatExpressionSection> sections;
    for (std::size_t i = 1; i < argsLength - 1; i += 2) {
        auto options = arrayMember(value, 1);
        if (!isObject(options)) {
            ctx.error("Collator options argument must be an object.");
            return ParseResult();
        }
        
        ParseResult text = ctx.parse(args[i], 1, ValueType);
        if (!text) return null;
        const kind = text.type.kind;
        if (kind !== 'string' && kind !== 'value' && kind !== 'null')
            return context.error(`Formatted text type must be 'string', 'value', or 'null'.`);
        
        const options = (args[i + 1]: any);
        if (typeof options !== "object" || Array.isArray(options))
            return context.error(`Format options argument must be an object.`);
        
        let scale = null;
        if (options['font-scale']) {
            scale = context.parse(options['font-scale'], 1, NumberType);
            if (!scale) return null;
        }
        
        let font = null;
        if (options['text-font']) {
            font = context.parse(options['text-font'], 1, array(StringType));
            if (!font) return null;
        }
        sections.push({text, scale, font});
    }
    
    return new FormatExpression(sections);

    auto options = arrayMember(value, 1);
    if (!isObject(options)) {
        ctx.error("Collator options argument must be an object.");
        return ParseResult();
    }
    
    const optional<Convertible> caseSensitiveOption = objectMember(options, "case-sensitive");
    ParseResult caseSensitive;
    if (caseSensitiveOption) {
        caseSensitive = ctx.parse(*caseSensitiveOption, 1, {type::Boolean});
    } else {
        caseSensitive = { std::make_unique<Literal>(false) };
    }
    if (!caseSensitive) {
        return ParseResult();
    }
    
    const optional<Convertible> diacriticSensitiveOption = objectMember(options, "diacritic-sensitive");
    ParseResult diacriticSensitive;
    if (diacriticSensitiveOption) {
        diacriticSensitive = ctx.parse(*diacriticSensitiveOption, 1, {type::Boolean});
    } else {
        diacriticSensitive = { std::make_unique<Literal>(false) };
    }
    if (!diacriticSensitive) {
        return ParseResult();
    }
    
    const optional<Convertible> localeOption = objectMember(options, "locale");
    ParseResult locale;
    if (localeOption) {
        locale = ctx.parse(*localeOption, 1, {type::String});
        if (!locale) {
            return ParseResult();
        }
    }
    
    return ParseResult(std::make_unique<FormatExpression>(std::move(*caseSensitive), std::move(*diacriticSensitive), std::move(locale)));
}

void FormatExpression::eachChild(const std::function<void(const Expression&)>& fn) const {
    fn(*caseSensitive);
    fn(*diacriticSensitive);
    if (locale) {
        fn(**locale);
    }
}

bool FormatExpression::operator==(const Expression& e) const {
    if (e.getKind() == Kind::FormatExpression) {
        auto rhs = static_cast<const FormatExpression*>(&e);
        if ((locale && (!rhs->locale || **locale != **(rhs->locale))) ||
            (!locale && rhs->locale)) {
            return false;
        }
        return *caseSensitive == *(rhs->caseSensitive) &&
        *diacriticSensitive == *(rhs->diacriticSensitive);
    }
    return false;
}

mbgl::Value FormatExpression::serialize() const {
    std::unordered_map<std::string, mbgl::Value> options;
    options["case-sensitive"] = caseSensitive->serialize();
    options["diacritic-sensitive"] = diacriticSensitive->serialize();
    if (locale) {
        options["locale"] = (*locale)->serialize();
    }
    return std::vector<mbgl::Value>{{ std::string("collator"), options }};
}

EvaluationResult FormatExpression::evaluate(const EvaluationContext& params) const {
    auto caseSensitiveResult = caseSensitive->evaluate(params);
    if (!caseSensitiveResult) {
        return caseSensitiveResult.error();
    }
    auto diacriticSensitiveResult = diacriticSensitive->evaluate(params);
    if (!diacriticSensitiveResult) {
        return diacriticSensitiveResult.error();
    }
    
    if (locale) {
        auto localeResult = (*locale)->evaluate(params);
        if (!localeResult) {
            return localeResult.error();
        }
        return Collator(caseSensitiveResult->get<bool>(), diacriticSensitiveResult->get<bool>(), localeResult->get<std::string>());
    } else {
        return Collator(caseSensitiveResult->get<bool>(), diacriticSensitiveResult->get<bool>());
    }
}

} // namespace expression
} // namespace style
} // namespace mbgl

