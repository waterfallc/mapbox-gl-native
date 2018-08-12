var spec = module.exports = require('../mapbox-gl-js/src/style-spec/reference/v8');

// Make temporary modifications here when Native doesn't have all features that JS has.
delete spec.paint_line['line-gradient']

console.log(JSON.stringify());

spec.layout_symbol['text-field']['type'] = "string"
spec.layout_symbol['text-field']['doc'] = "Value to use for a text label."

delete spec.expression_name['values']['format']
spec.expression_name['values']['concat']['doc'] = "Returns a string consisting of the concatenation of the inputs."
