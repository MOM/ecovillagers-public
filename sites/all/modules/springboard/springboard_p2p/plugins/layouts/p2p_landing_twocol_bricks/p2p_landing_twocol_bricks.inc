<?php

/**
 * @file
 * Implementation for the two column bricked layout
 */

// Plugin definition
$plugin = array(
  'title' => t('P2P Landing Two column bricks'),
  'category' => t('Peer to Peer'),
  'icon' => 'p2p_landing_twocol_bricks.png',
  'theme' => 'p2p_landing_twocol_bricks',
  'css' => 'p2p_landing_twocol_bricks.css',
  'regions' => array(
    'top' => t('Top'),
    'middle_left' => t('Middle Left'),
    'middle_right' => t('Middle Right'),
    'bottom' => t('Bottom'),
  ),
);
