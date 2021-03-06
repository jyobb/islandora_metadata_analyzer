<?php
/*
 * @params Collection $pid, Datastream type (MODS, DC)
 *
 * Test the PID to ensure it is a collection and query for all 
 * child objects.
 *
 * Send result to datastream specific analyzer function
 *
 */
function islandora_metadata_analyzer($params){

  $title = $params['result_set_title'];
  $pid = $params['pid'];
  $stream = $params['stream'];
  $capture_fields_string = $params['capture_fields'];

  $capture_fields = explode(',', $capture_fields_string);
  $collections = array('islandora:collectionCModel', 'islandora:bookCModel');
  $start_time = microtime(true);

  $params['start_time'] = $start_time;

  $query = <<<EOQ
  SELECT ?pid FROM <#ri>
WHERE {
    {
  ?pid <fedora-rels-ext:isMemberOf> <info:fedora/$pid>
  }
  UNION
  {
  ?pid <fedora-rels-ext:isMemberOfCollection> <info:fedora/$pid>
  }
}
EOQ;
  $connection = islandora_get_tuque_connection();

  $sparql_count = $connection->repository->ri->countQuery($query, 'sparql');
  $results = $connection->repository->ri->sparqlQuery($query); 
                             
  $analysis_results = array();
  $data = array();
  $path_data = array();

$pid_list = array();

foreach ($results as $result) {
  $fedoraObject = islandora_object_load($result['pid']['value']);
  $pid_list[] = $fedoraObject->id;
  $relationships = $fedoraObject->relationships->get('info:fedora/fedora-system:def/model#', 'hasModel');
  if(in_array($relationships[0]['object']['value'], $collections)){
    //need to recurse
  } else {
    if($stream == 'DC'){
      module_load_include('inc', 'islandora_metadata_analyzer', 'includes/DC_analyzer');

      islandora_DC_metadata_analyzer($fedoraObject, $analysis_results, $data, $params, $path_data);              
    }elseif($stream == 'MODS'){
      module_load_include('inc', 'islandora_metadata_analyzer', 'includes/MODS_analyzer');

      islandora_MODS_metadata_analyzer($fedoraObject, $analysis_results, $data, $params, $path_data);              
     
    }
  }

}


$result_id = islandora_metadata_analyzer_save_analyzer_results($analysis_results, $params, $sparql_count);

islandora_metadata_analyzer_save_query_pids($result_id, $pid_list);

//Check to see if they saved data first
islandora_metadata_analyzer_save_analyzer_data($result_id, $data);

islandora_metadata_analyzer_save_path_data($result_id, $path_data);


}


/*
 * @params results_id pid_list
 *
 * Save list of all pids processed
 *
 */ 
function islandora_metadata_analyzer_save_query_pids($result_id, $pid_list){

$values = array();
foreach($pid_list as $pid){
  $values[] = array('result_id' => $result_id, 'pid' => $pid); 
}

$query = db_insert('islandora_metadata_analyzer_pids')->fields(array('result_id', 'pid'));
foreach ($values as $record) {
  $query->values($record);
}
$query->execute();

}



/*
 * @params result_id path_data
 *
 * Save path info and pids to 2 separate database tables.
 *
 */
function islandora_metadata_analyzer_save_path_data($result_id, $data){

foreach($data as $path => $metadata){

  $path_id = db_insert('islandora_metadata_analyzer_all_paths')
    ->fields(array(
    'result_id' => $result_id,
    'path' => $path,
  ))
  ->execute();

    foreach($metadata as $data_val){
      $path_data_id = db_insert('islandora_metadata_analyzer_all_pids')
        ->fields(array(
        'path_id' => $path_id,
        'pid' => substr($data_val, 0, 126),
		       ))
      ->execute();
    }

}

}






/*
 * @params result_id data
 *
 * Save path info, metadata, and pids to 3 separate database tables.
 *
 */
function islandora_metadata_analyzer_save_analyzer_data($result_id, $data){

foreach($data as $path => $metadata){

  $path_id = db_insert('islandora_metadata_analyzer_paths') // Table name no longer needs {}
    ->fields(array(
    'result_id' => $result_id,
    'path' => $path,
  ))
  ->execute();

  $tmp_data = array();
    foreach($metadata as $data_val => $pids){
      $path_data_id = db_insert('islandora_metadata_analyzer_path_data') // Table name no longer needs {}
        ->fields(array(
        'path_id' => $path_id,
        'path_data' => substr($data_val, 0, 126),
		       ))
      ->execute();
      $tmp_data[$path_data_id] = $pids;
    }

    foreach($tmp_data as $path_data_key => $pids){
      foreach($pids as $pid){
        $path_id = db_insert('islandora_metadata_analyzer_data_pids') // Table name no longer needs {}
          ->fields(array(
          'path_data_id' => $path_data_key,
          'pid' => $pid,
        ))
        ->execute();
      }
    }
}

}

/*
 * @params analysis_results, result_set_title, pid, start_time, count
 *
 * Save analysis array to database 
 *
 */
//function islandora_metadata_analyzer_save_analyzer_results($analysis_results, $result_set_title, $pid, $start_time, $count){
function islandora_metadata_analyzer_save_analyzer_results($analysis_results, $params, $count){
  //function islandora_metadata_analyzer_save_analyzer_results($params, $count){

$result_set_title = $params['result_set_title'];
$pid = $params['pid'];
$start_time = $params['start_time'];
$stream = $params['stream'];

$end_time = microtime(true);
$query_time = $end_time - $start_time;
$nice_time = microtimeFormat($query_time);

$result_id = db_insert('islandora_metadata_analyzer_results') // Table name no longer needs {}
  ->fields(array(
  'query_time' => $nice_time,
  'pid' => $pid,
  'stream' => $stream,
  'title' => $result_set_title,
  'element_data' => serialize($analysis_results),
  'record_count' => $count,
))
->execute();

return $result_id;

}


/*
 * @params result_id
 *
 * Delete analysis result
 *
 */ 
function islandora_metadata_analyzer_delete_result($result_id) {

$data_result = db_query("delete from islandora_metadata_analyzer_results where result_id = :result_id", array(":result_id" => $result_id));

drupal_goto('metadata_analyzer/results');

}




/*
 * @params duration
 *
 * Reformat microsecond time
 */
function microtimeFormat($duration)
{
    $hours = (int)($duration/60/60);
    $minutes = (int)($duration/60)-$hours*60;
    $seconds = $duration-$hours*60*60-$minutes*60;
    return $hours . ":" . $minutes . ":" . number_format((float)$seconds, 2, '.', '');
}
