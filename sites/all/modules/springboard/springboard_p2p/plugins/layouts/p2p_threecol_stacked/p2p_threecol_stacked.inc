<?php

// Plugin definition
$plugin = array(
  'title' => t('P2P Three column stacked'),
  'category' => t('Peer to Peer'),
  'icon' => 'p2p_threecol_stacked.png',
  'theme' => 'panels_p2p_threecol_stacked',
  'css' => 'p2p_threecol_stacked.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left side'),
    'middle' => t('Middle column'),
    'right' => t('Right side'),
    'bottom' => t('Bottom'),
  ),
);
