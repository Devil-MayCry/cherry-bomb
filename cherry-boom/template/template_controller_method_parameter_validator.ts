let validator: Validator = new Validator();

${method_parameters_items}

if (validator.hasErrors()) {
  res.json(new BadRequestResponse(validator.errors));
  return;
}
