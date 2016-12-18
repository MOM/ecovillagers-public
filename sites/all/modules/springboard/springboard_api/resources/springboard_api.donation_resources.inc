<?php

/**
 * @file
 * Resource definition callbacks for donation service resource.
 */

/**
 *
 *
 */
function springboard_api_donation_resource_index() {

}

/**
 *
 *
 */
function springboard_api_donation_resource_retrieve() {

}

/**
 *
 *
 */
function springboard_api_donation_resource_create() {
  /*
   required fields:
  first name
  last name
  email
  address 1
  city
  state
  country
  zip
  payment details
    - varies by payment type
   */
}

/**
 *
 *
 */
function springboard_api_donation_resource_access() {
  return TRUE;
}