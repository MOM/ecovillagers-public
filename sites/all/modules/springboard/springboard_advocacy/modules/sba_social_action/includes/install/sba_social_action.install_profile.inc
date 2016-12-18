<?php

/**
 * @file
 * Install helper functions for profile fields.
 */

/**
 * Create the social action user profile fields.
 */
function _sbp_social_action_create_user_profile_fields() {
  _sba_social_action_create_zip_plus_four();
  _sba_social_action_create_twitter_screen_name();
  _sba_social_action_create_twitter_id_str();
  _sba_social_action_create_twitter_status_count();
  _sba_social_action_create_twitter_following_count();
  _sba_social_action_create_twitter_followers_count();
  _sba_social_action_create_twitter_created_at();
}

/**
 * Create the zip plus four user profile field.
 *
 * Done separately so can be used in update hook.
 */
function _sba_social_action_create_zip_plus_four() {

  $profile_zip_plus_four = array(
    'label' => t('Zip+4'),
    'field_name' => 'sbp_zip_plus_four',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  $zip_exists = field_info_field('sbp_zip_plus_four');

  if (empty($zip_exists)) {
    field_create_field($profile_zip_plus_four);
  }

  $instance_exists = field_info_instance('user', 'sbp_zip_plus_four', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($profile_zip_plus_four, $instance);
    field_create_instance($instance);
  }

  $field_group = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  if ($field_group) {
    if(empty($field_group->children['sbp_zip_plus_four'])) {
      $field_group->children[] = 'sbp_zip_plus_four';
      ctools_export_crud_save($table, $field_group);
    }
  }
}

/**
 * Create the zip plus four user profile field.
 *
 * Done separately so can be used in update hook.
 */
function _sba_social_action_create_twitter_screen_name() {

  $screen_name = array(
    'label' => t('Twitter Screen Name'),
    'field_name' => 'sbp_twitter_screen_name',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  $zip_exists = field_info_field('sbp_twitter_screen_name');

  if (empty($zip_exists)) {
    field_create_field($screen_name);
  }

  $instance_exists = field_info_instance('user', 'sbp_twitter_screen_name', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($screen_name, $instance);
    field_create_instance($instance);
  }

  $field_group = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  if ($field_group) {
    if(empty($field_group->children['sbp_twitter_screen_name'])) {
      $field_group->children[] = 'sbp_twitter_screen_name';
      ctools_export_crud_save($table, $field_group);
    }
  }
}

function _sba_social_action_create_twitter_id_str() {

  $screen_name = array(
    'label' => t('Twitter ID String'),
    'field_name' => 'sbp_twitter_id_str',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  $zip_exists = field_info_field('sbp_twitter_id_str');

  if (empty($zip_exists)) {
    field_create_field($screen_name);
  }

  $instance_exists = field_info_instance('user', 'sbp_twitter_id_str', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($screen_name, $instance);
    field_create_instance($instance);
  }

  $field_group = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  if ($field_group) {
    if(empty($field_group->children['sbp_twitter_id_str'])) {
      $field_group->children[] = 'sbp_twitter_id_str';
      ctools_export_crud_save($table, $field_group);
    }
  }
}

function _sba_social_action_create_twitter_following_count() {

  $screen_name = array(
    'label' => t('Twitter Following Count'),
    'field_name' => 'sbp_twitter_following_count',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  $zip_exists = field_info_field('sbp_twitter_following_count');

  if (empty($zip_exists)) {
    field_create_field($screen_name);
  }

  $instance_exists = field_info_instance('user', 'sbp_twitter_following_count', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($screen_name, $instance);
    field_create_instance($instance);
  }

  $field_group = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  if ($field_group) {
    if(empty($field_group->children['sbp_twitter_following_count'])) {
      $field_group->children[] = 'sbp_twitter_following_count';
      ctools_export_crud_save($table, $field_group);
    }
  }
}


function _sba_social_action_create_twitter_followers_count() {

  $screen_name = array(
    'label' => t('Twitter Followers Count'),
    'field_name' => 'sbp_twitter_followers_count',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  $zip_exists = field_info_field('sbp_twitter_followers_count');

  if (empty($zip_exists)) {
    field_create_field($screen_name);
  }

  $instance_exists = field_info_instance('user', 'sbp_twitter_followers_count', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($screen_name, $instance);
    field_create_instance($instance);
  }

  $field_group = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  if ($field_group) {
    if(empty($field_group->children['sbp_twitter_followers_count'])) {
      $field_group->children[] = 'sbp_twitter_followers_count';
      ctools_export_crud_save($table, $field_group);
    }
  }
}


function _sba_social_action_create_twitter_status_count() {

  $screen_name = array(
    'label' => t('Twitter Status Count'),
    'field_name' => 'sbp_twitter_status_count',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  $zip_exists = field_info_field('sbp_twitter_status_count');

  if (empty($zip_exists)) {
    field_create_field($screen_name);
  }

  $instance_exists = field_info_instance('user', 'sbp_twitter_status_count', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($screen_name, $instance);
    field_create_instance($instance);
  }

  $field_group = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  if ($field_group) {
    if(empty($field_group->children['sbp_twitter_status_count'])) {
      $field_group->children[] = 'sbp_twitter_status_count';
      ctools_export_crud_save($table, $field_group);
    }
  }
}

function _sba_social_action_create_twitter_created_at() {

  $screen_name = array(
    'label' => t('Twitter Created At'),
    'field_name' => 'sbp_twitter_created_at',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  $zip_exists = field_info_field('sbp_twitter_created_at');

  if (empty($zip_exists)) {
    field_create_field($screen_name);
  }

  $instance_exists = field_info_instance('user', 'sbp_twitter_created_at', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($screen_name, $instance);
    field_create_instance($instance);
  }

  $field_group = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  if ($field_group) {
    if(empty($field_group->children['sbp_twitter_created_at'])) {
      $field_group->children[] = 'sbp_twitter_created_at';
      ctools_export_crud_save($table, $field_group);
    }
  }
}
