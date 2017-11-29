<?php

/**
 * @file
 * Functions for listing products through the API.
 */

/**
 * List products.
 *
 * @param string $type
 *   Optional type of product to filter the query, defaults to NULL.
 * @param string $api_key
 *   The api key currently being used.
 * @param int $limit
 *   The number of entities to retrieve.
 * @param int $offset
 *   The zero-based index from which to start retrieving entities.
 */
function springboard_api_products_index($type, $api_key, $limit, $offset) {
  // Build a query to load products.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'commerce_product');
  $query->range($offset, $limit);

  // Add the specified type to the query.
  if (!empty($type)) {
    $query->propertyCondition('type', $type);
  }

  // Execute the query and load the entities it returns if any.
  $result = $query->execute();

  $return = array();

  if (!empty($result['commerce_product'])) {
    $entities = entity_load('commerce_product', array_keys($result['commerce_product']));

    foreach ($entities as $entity_id => &$entity) {
      // Add simplified fields to the entity object for certain field types.
      $item = array(
        'sku' => $entity->sku,
        'title' => $entity->title,
        'status' => $entity->status,
        'product_id' => $entity->product_id,
        'type' => $entity->type,
      );

      // Flatten field values.
      $clone = clone($entity);
      $bundle = field_extract_bundle('commerce_product', $clone);
      $clone_wrapper = entity_metadata_wrapper('commerce_product', $clone);

      // Loop over every field instance on the given entity.
      foreach (field_info_instances('commerce_product', $bundle) as $field_name => $instance) {
        // Set the value to the raw wrapper value.
        $item[$field_name] = $clone_wrapper->{$field_name}->raw();
      }

      // Add this item to the return array.
      $return[] = $item;
    }
  }

  return $return;
}
