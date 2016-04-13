<?php

function islandora_metadata_analyzer_results(){

  $result = db_query("SELECT result_id, title FROM {islandora_metadata_analyzer_results}");
  $outResult = array();

  foreach( $result as $record ){
    $outResult[$record->result_id] = $record->title;
  }

 $output = theme('results_list', array('resultArray' => $outResult));

 return $output;
}

function islandora_metadata_analyzer_element_counts($result_id){

  $result = db_query("SELECT result_id, title, element_data, pid, query_time, record_count, stream FROM {islandora_metadata_analyzer_results} where result_id = :result_id", array(":result_id" => $result_id))->fetchObject();

//$path_results = db_query("select path, path_id FROM {islandora_metadata_analyzer_all_paths} where result_id = :result_id ORDER BY path", array(":result_id" => $result_id));

$path_results = db_query("select p.path path, ap.path_id path_id, count(ap.path_id) count from {islandora_metadata_analyzer_all_paths} p, {islandora_metadata_analyzer_all_pids} ap where p.path_id = ap.path_id and p.result_id = :result_id group by ap.path_id order by p.path", array(":result_id" => $result_id));

$path_data = array();
foreach($path_results as $pr){
$path_data[] = (array) $pr;
}

$data_result = db_query("select p.path_id, p.path from {islandora_metadata_analyzer_paths} p  where p.result_id = :result_id", array(":result_id" => $result_id));

$theme_data = array();
foreach($data_result as $td){
 $theme_data[] = (array) $td;
}

  //$output = theme('element_count', array('result_id' => $result->result_id, 'title' => $result->title, 'pid' => $result->pid, 'query_time' => $result->query_time, 'countArray' => $result->element_data, 'record_count' => $result->record_count, 'stream' => $result->stream, 'path_data' => $theme_data));

$output = theme('element_count', array('result_id' => $result_id, 'title' => $result->title, 'pid' => $result->pid, 'query_time' => $result->query_time, 'countArray' => $path_data, 'record_count' => $result->record_count, 'stream' => $result->stream, 'path_data' => $theme_data));

 return $output;
}


function islandora_metadata_analyzer_delete_result($result_id) {

$data_result = db_query("delete from islandora_metadata_analyzer_results where result_id = :result_id", array(":result_id" => $result_id));

drupal_goto('metadata_analyzer/results');

//$output = islandora_metadata_analyzer_results();

//return $output;
}

