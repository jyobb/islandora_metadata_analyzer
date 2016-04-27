<?php

/*
 * @params database id of metadata entry in islandora_metadata_analyzer_path_data table
 *
 * Query database for list of pids and send file to user
 *
 * Download PIDS that have a specific data element
 */
function islandora_metadata_analyzer_download_pids($path_data_id){

  $data_title = db_query("select * from {islandora_metadata_analyzer_path_data}  where path_data_id = :path_data_id", array(":path_data_id" => $path_data_id))->fetchObject(); 

  $data_data = db_query("select * from {islandora_metadata_analyzer_data_pids} where path_data_id = :path_data_id order by pid", array(":path_data_id" => $path_data_id)); 

  $out = "";
  foreach($data_data as $data_content){
    $out.= $data_content->pid_id . ', ';
  }

  header("Content-Type: text/plain"); //the content type that I am exporting
  header("Content-Disposition: Attachment; filename=". $data_title->path_data);
  header("Pragma: no-cache"); //I don't want this to be cached because it is constantly changing
  echo $out;
  exit(0);

}

/*
 * @params queryType path_id for data
 *
 * Ajax function that updates page with pids
 * 
 * Updates page with PIDS that have a specific data element
 */
function islandora_metadata_analyzer_data_ajax($type='ajax', $path_data_id=0){
  $output = islandora_metadata_analyzer_load_data_data($path_data_id);
  
  if($type == 'ajax'){
    $commands = array();
    $commands[] = ajax_command_replace('#datadata-'.$path_data_id, '<div class="removepathpids" pathid=' . $path_data_id .'">' . $output . '</div>');
    $page = array('#type' => 'ajax', '#commands' => $commands);
    ajax_deliver($page);
  } 

}

/*
 * @params path_data_id for data
 *
 * Ajax helper function that retrieves data pids
 *
 * Feed data to the above function
 */
function islandora_metadata_analyzer_load_data_data($path_data_id){

$data_data = db_query("select * from {islandora_metadata_analyzer_data_pids} p where p.path_data_id = :path_data_id order by pid", array(":path_data_id" => $path_data_id)); 
$out = "";
foreach($data_data as $data_content){
  $out.= '<div id="datadata-' . $data_content->pid_id . '">' . $data_content->pid . '</div>';
}
return $out;
}

/*
 * @params queryType path_id for data
 *
 * Ajax function that updates page with element data
 * 
 * Get the data elements at a specific path
 */
function islandora_metadata_analyzer_path_ajax($type='ajax', $path_id=0){
  $output = islandora_metadata_analyzer_load_path_data($path_id);
  
  if($type == 'ajax'){
    $commands = array();
    $commands[] = ajax_command_replace('#pathdata-'.$path_id, '<div class="removedataelements" pathid=' . $path_id .'">' . $output .'</div>');
    $page = array('#type' => 'ajax', '#commands' => $commands);
    ajax_deliver($page);
  } 

}

/*
 * @params path_id for data
 *
 * Ajax helper function that retrieves data data
 *
 * Feed data elements to the above function
 */
function islandora_metadata_analyzer_load_path_data($path_id){

$path_data = db_query("select * from {islandora_metadata_analyzer_path_data} p where p.path_id = :path_id", array(":path_id" => $path_id)); 
$out = '<div class="hideajax">Hide Data</div>';

foreach($path_data as $path_content){
  $tdata = trim($path_content->path_data);
  if(strlen($tdata) != 0){ 
    $link = l(t($path_content->path_data), 'islandora_metadata_analyzer/ajax-data/nojs/' . $path_content->path_data_id, array('attributes' => array('class' => array('use-ajax'))));
    $downloadlink = l(t($path_content->path_data), 'islandora_metadata_analyzer/downloads/' . $path_content->path_data_id );
    $out.= '<div id="pathdata-' . $path_content->path_data_id . '">' . $link . ' Download PIDs for: ' . $downloadlink . '</div><div id="datadata-' . $path_content->path_data_id . '"></div>';

  }else{
      $out .= '<div id="pathdata-' . $path_id . '">No Data</div>';
  }
}




return $out;
}

/*
 * @params path_id for data
 *
 * Ajax helper function that updates the #allpathpids class with
 * data from the helper function
 *
 * Get PIDS that have a specific path
 */
function islandora_metadata_analyzer_allpath_ajax($type='ajax', $path_id=0){
  $output = islandora_metadata_analyzer_load_pid_data($path_id);

  if($type == 'ajax'){
    $commands = array();
    $commands[] = ajax_command_replace('#allpathpids-'.$path_id, '<div class="removepids" pathid=' . $path_id .'">' . $output . '</div>');
    $page = array('#type' => 'ajax', '#commands' => $commands);
    ajax_deliver($page);
  } 
}

/*
 * @params path_id for data
 *
 * Helper function that queries the database to find the pids that have the path referenced
 * by the given path_id
 *
 */
function islandora_metadata_analyzer_load_pid_data($path_id){

$path_data = db_query("select * from {islandora_metadata_analyzer_all_pids} p where p.path_id = :path_id order by pid", array(":path_id" => $path_id)); 
$out = '<div class="hideajax">Hide found PIDS</div>';
foreach($path_data as $pid_data){
  $out .= $pid_data->pid . ', ';

}
return $out;
}

/*
 * @params path_id for data
 *
 * Queries the database to find the pids that have the path referenced
 * by the given path_id and sends a comma separated list to the browser
 *
 */
function islandora_metadata_analyzer_download_all_pids($path_id){


  $data_title = db_query("select * from {islandora_metadata_analyzer_all_paths} p, {islandora_metadata_analyzer_results} r where r.result_id = p.result_id and p.path_id = :path_id" , array(":path_id" => $path_id))->fetchObject(); 

  $pid_list = db_query("select * from {islandora_metadata_analyzer_all_pids} p where p.path_id = :path_id order by pid", array(":path_id" => $path_id));  

  $out = "";
  foreach($pid_list as $pids){
    $out.= $pids->pid . ', ';
  }

  header("Content-Type: text/plain"); //the content type that I am exporting
  header("Content-Disposition: Attachment; filename=". $data_title->title . ".txt");
  header("Pragma: no-cache"); //I don't want this to be cached because it is constantly changing
  echo $out;
  exit(0);

}



/*
 * @params path_id for data
 *
 * Ajax helper function that updates the #missingallpathpids class with
 * list of PIDS missing a path
 *
 */
function islandora_metadata_analyzer_allpath_missing_ajax($type='ajax', $path_id=0){
  $output = islandora_metadata_analyzer_load_pid_missing_data($path_id);
  if($type == 'ajax'){
    $commands = array();
    $commands[] = ajax_command_replace('#missingallpathpids-'.$path_id, '<div class="removemissingpids" pathid=' . $path_id .'">' . $output . '</div>');
    $page = array('#type' => 'ajax', '#commands' => $commands);
    ajax_deliver($page);
  } 

}

/*
 * @params path_id for data
 *
 * Helper function that queries the database to find the pids that do not have the path referenced
 * by the given path_id
 *
 */
function islandora_metadata_analyzer_load_pid_missing_data($path_id){

  $path_data = db_query("select pp.pid pid, pp.result_id result_id from {islandora_metadata_analyzer_pids} pp left join {islandora_metadata_analyzer_all_paths} ap on ap.result_id = pp.result_id left join {islandora_metadata_analyzer_all_pids} apa on apa.path_id = ap.path_id and apa.pid = pp.pid where ap.path_id = :path_id and apa.pid is NULL order by pp.pid", array(":path_id" => $path_id));

$out = '<div class="hideajaxmissing">Hide missing PIDS</div>';
foreach($path_data as $pid_data){
  $out .= $pid_data->pid . ', ';

}
return $out;
}

/*
 * @params path_id for data
 *
 * Queries the database to find the pids that do not have the path referenced
 * by the given path_id and sends a comma separated list to the browser
 *
 */
function islandora_metadata_analyzer_download_all_missing_pids($path_id){

  $data_title = db_query("select * from {islandora_metadata_analyzer_all_paths} p, {islandora_metadata_analyzer_results} r where r.result_id = p.result_id and p.path_id = :path_id" , array(":path_id" => $path_id))->fetchObject(); 

  $missing_pid_list = db_query("select pp.pid pid, pp.result_id result_id from {islandora_metadata_analyzer_pids} pp left join {islandora_metadata_analyzer_all_paths} ap on ap.result_id = pp.result_id left join {islandora_metadata_analyzer_all_pids} apa on apa.path_id = ap.path_id and apa.pid = pp.pid where ap.path_id = :path_id and apa.pid is NULL order by pp.pid", array(":path_id" => $path_id));

  $out = "";
  foreach($missing_pid_list as $pids){
    $out.= $pids->pid . ', ';
  }

  header("Content-Type: text/plain"); //the content type that I am exporting
  header("Content-Disposition: Attachment; filename=". $data_title->title . ".txt");
  header("Pragma: no-cache"); //I don't want this to be cached because it is constantly changing
  echo $out;
  exit(0);

}




?>