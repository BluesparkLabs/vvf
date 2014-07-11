<?php

/**
 * @file
 * Definition of views_handler_field_variable.
 */

/**
 * A handler to provide a field that display system variables.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_variable extends views_handler_field {

  /**
   * Called to add the field to a query.
   */
  function query() {
    // Do nothing -- to override the parent query.
  }

  /**
   * The function used to retrieve the variable value.
   *
   * @var mixed
   */
  public $function = NULL;

  /**
   * Constructs a new field handler.
   */
  function construct() {
    parent::construct();

    $this->function = module_exists('variable') ? 'variable_get_value' : 'variable_get';
  }

  /**
   * Information about options for all kinds of purposes will be held here.
   *
   * @return array
   *   Returns the options of this handler/plugin.
   *
   * @see views_object::export_option()
   * @see views_object::export_option_always()
   * @see views_object::unpack_translatable()
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['variable_name'] = array('default' => '');
    return $options;
  }

  /**
   * Build the options form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['variable'] = array(
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#title' => t('Drupal variable'),
    );

    $form['variable']['variable_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Variable name'),
      '#default_value' => $this->options['variable_name'],
      '#description' => t('You may enter data from this view as per the "Replacement patterns" below.'),
    );

    $form['variable']['variable_help'] = $form['alter']['help'];
    unset($form['variable_help']['#dependency']);
  }

  /**
   * Render the field.
   *
   * @param stdClass $values
   *   The values retrieved from the database.
   */
  function render($values) {
    // Return the variable value and continue with the process.
    return call_user_func($this->function, $this->tokenize_value($this->tokenize_value($this->options['variable_name'])));
  }
}
