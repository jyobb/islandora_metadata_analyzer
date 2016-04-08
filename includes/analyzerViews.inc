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

  //$data_result = db_query("select pd.path_id, p.path, pd.path_data, pd.path_data_id, pidd.pid_id, pidd.pid from {islandora_metadata_analyzer_paths} p, {islandora_metadata_analyzer_path_data} pd, {islandora_metadata_analyzer_data_pids} pidd where pd.path_id = p.path_id and pidd.path_data_id = pd.path_data_id and p.result_id = :result_id", array(":result_id" => $result_id));

$data_result = db_query("select p.path_id, p.path from {islandora_metadata_analyzer_paths} p  where p.result_id = :result_id", array(":result_id" => $result_id));

$theme_data = array();
foreach($data_result as $td){
 $theme_data[] = (array) $td;
}





//dpm($theme_data);

  $output = theme('element_count', array('result_id' => $result->result_id, 'title' => $result->title, 'pid' => $result->pid, 'query_time' => $result->query_time, 'countArray' => $result->element_data, 'record_count' => $result->record_count, 'stream' => $result->stream, 'path_data' => $theme_data));

 return $output;
}