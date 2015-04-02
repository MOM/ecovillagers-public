<?php
/**
 * @file
 * Context plugin file to provide changing the page wrapper as a context
 * reaction.
 */

/**
 * Expose page wrappers as context reactions.
 */
class context_reaction_page_wrappers extends context_reaction {

  /**
   * Grab the available page wrappers and provide them as a reaction for context.
   *
   * @param $context
   *   The context as passed from context module.
   *
   * @return array
   *   The FAPI array as read by context module.
   */
  function options_form($context) {

    $wrappers = _page_wrappers_available_wrappers();
    $options = (isset($wrappers)) ? $wrappers : array('No page wrappers created');

    $settings = $this->fetch_from_context($context);

    $form = array(
      '#tree' => TRUE,
      '#title' => t('Page wrappers'),

      'page_wrapper' => array(
        '#title' => t('Active page wrapper'),
        '#description' => t('Choose a page wrapper to use when this context is active.'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($settings['page_wrapper']) ? $settings['page_wrapper'] : 0,
      ),
    );
    return $form;
  }

  /**
   * Return the page wrapper based on the context
   *
   * @return string | null
   *   String of the page_wrapper name, or NULL if not to be altered.
   */
  function execute() {
    $page_wrapper = NULL;

    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions['active_page_wrapper']['page_wrapper'])) {
        $page_wrapper = $context->reactions['active_page_wrapper']['page_wrapper'];
      }
    }

    return $page_wrapper;
  }
}
