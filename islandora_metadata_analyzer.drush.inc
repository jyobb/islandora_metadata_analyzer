<?php

/**
 * @file
 * Drush hooks.
 */

/**
 * Implements hook_drush_command().
 */
function islandora_metadata_analyzer_drush_command() {
  $items = array();

  $items['islandora_metadata_analyzer'] = array(
    'aliases' => array('imac'),
    'description' => 'Analyze the metadata of the objects in a collection.',
    'drupal dependencies' => array('islandora_metadata_analyzer'),
    'examples' => array(
      'drush -v --user=admin --uri=http://saskhistoryonline.ca islandora --title="result set title" --metadata_stream="MODS" --collection_PID="collection:pid" --element_list=element1, element4',
    ),
    'options' => array(
      'title' => array(
        'description' => 'A title for the result set.',
        'required' => TRUE,
      ),
      'metadata_stream' => array(
        'description' => 'Datastream to analyze MODS or DC.',
        'required' => TRUE,
      ),
      'collection_PID' => array(
        'description' => 'PID of collection to analyze.',
        'required' => TRUE,
      ),
      'element_list' => array(
        'description' => 'A comma separated list of TOP level tags to capture.',
        'required' => FALSE,
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

return $items;

}


/**
 * Implements drush_COMMAND_validate() for islandora_metadata_analyzer.
 */
function drush_islandora_metadata_analyzer_validate() {
  $streams = array('MODS', 'DC');
  $datastream = drush_get_option('metadata_stream');
  if (!in_array($datastream, $streams)) {
    drush_set_error('INVALID DATASTREAM');
  }
}



function drush_islandora_metadata_analyzer(){

  $stream = drush_get_option('metadata_stream');
  $collection_pid = drush_get_option('collection_PID');
  $result_set_title = drush_get_option('title');
  $capture_fields = drush_get_option('element_list');

  $params = array('capture_fields' => $capture_field, 'result_set_title' => $result_set_title, 'datastream' => $stream);  

  module_load_include('inc', 'islandora_metadata_analyzer', 'includes/analyzer');

  islandora_metadata_analyzer($collection_pid, $stream, $params);

}