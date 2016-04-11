<?php

/* @params $simplexmlinterator, parent pid, results array, data array, element name, parameters
 *
 * Add key to path to build full path to element with data
 * Get attributes of current element and process element
 */
function newprocessDocument($sxe, $pid, &$results, &$data, $key=NULL, &$params, &$path_data){

 
  for ($sxe->rewind(); $sxe->valid(); $sxe->next()) {
//dpm($pid . " : " . $key);
    $path = $key . "/" . $sxe->key(); 

    newprocessElement($sxe, $results, $data, $pid, $path, $params, $path_data);
  
    //$val = strval($sxe->current());

    //Now lets think of the children
    if ($sxe->hasChildren()) {
      $results[$sxe->key()]['children'] = array();
      newprocessDocument($sxe->current(), $pid, $results[$sxe->key()]['children'], $data, $path, $params, $path_data);
    }
  }
return;
}


/*
 * @params simpleXMLIterator, results array, data array, current pid, xml path, params
 *
 * Capture element and attributes, if the element is one we want to capture add it
 * to the data array
 *
 * Add all elements to the results array and count them
 */
function newprocessElement($elementIterator, &$results, &$data, $pid, $path, &$params, &$path_data){

  $capture_fields_string = $params['capture_fields'];
  $capture_fields = explode(',', $capture_fields_string);
  //$capture_options = $params['capture_options'];
  $stream_root = $params['stream_root'];
  $element = $elementIterator->key();	 
  $element_value = strval($elementIterator->current());
  $match_offset = strlen($stream_root);


  $at = "@";
  $attrs = (array)$elementIterator->current()->attributes();
  if(array_key_exists('@attributes', $attrs)){
    foreach($attrs['@attributes'] as $k => $v){
      $at .= $k . "=" . $v . ",";
    }
  }

   // We have what we need so add to data array 
   // this is where the actual element value and pids
   // are caputured 
   // Test to see we have an element value  
  if((strlen($element_value) != 0) && !empty($capture_fields_string)){

    // Test to see if we want this field
    foreach($capture_fields as $field){
      $has_field = strpos($path, $field);
    }    

    //Here we have data and want to capture
    if($has_field == $match_offset){
      if(array_key_exists($path.$at, $data)){  			   
        if(array_key_exists( $element_value, $data[$path.$at])){
          array_push($data[$path.$at][$element_value], $pid);
        }else{
          $data[$path.$at][$element_value] = array($pid);
        }
      }else{
        $data[$path.$at][$element_value] = array($pid);
      }
    }
  }
  //End capture of the paths
  
    //Capture all paths and the pids that exist
    if(strlen($element_value) != 0 ){
     if(array_key_exists($path.$at, $path_data)){  			   
        if(!in_array( $pid, $path_data[$path.$at])){
          array_push($path_data[$path.$at], $pid);
        }else{
          $path_data[$path.$at]= array($pid);
        }
      }else{
        $path_data[$path.$at] = array($pid);
      }
}







    //This section collects the elements and counts them
    //The key exists
    if(array_key_exists($element, $results)){ 
     //increment count
        $results[$element]['count']++;
      if(array_key_exists($at, $results[$element]['attributes'])) {
        $results[$element]['attributes'][$at]++;
      } else {
        $results[$element]['attributes'][$at] = 1;
      }

    }else{
      $results[$element] = array('count' => 1, 'attributes' => array(), 'children' => array(), 'pids' => array($pid));
    }

return;

}




