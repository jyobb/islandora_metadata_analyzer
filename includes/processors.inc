<?php

/* @params $simplexmlinterator, parent pid, results array, data array, element name, parameters
 *
 * Add key to path to build full path to element with data
 * Get attributes of current element and process element
 */
function newprocessDocument($sxe, $pid, &$results, &$data, $key=NULL, &$params){

  for ($sxe->rewind(); $sxe->valid(); $sxe->next()) {
 
    $path = $key . "/" . $sxe->key(); 

    newprocessElement($sxe, $results, $data, $pid, $path, $params);
  
    //$val = strval($sxe->current());

    //Now lets think of the children
    if ($sxe->hasChildren()) {
      $results[$sxe->key()]['children'] = array();
      newprocessDocument($sxe->current(), $pid, $results[$sxe->key()]['children'], $data, $path, $params);
    }
  }
return;
}



function newprocessElement($elementIterator, &$results, &$data, $pid, $path, &$params){

  $capture_fields_string = $params['capture_fields'];
  $capture_fields = explode(',', $capture_fields_string);
  $capture_options = $params['capture_options'];

  $element = $elementIterator->key();	 
  $element_value = strval($elementIterator->current());

  
  $at = "@";
  $attrs = (array)$elementIterator->current()->attributes();
  if(array_key_exists('@attributes', $attrs)){
    foreach($attrs['@attributes'] as $k => $v){
      $at .= $k . "=" . $v . " ";
    }
  }
  
   // We have what we need so add to data array 
   // this is where the actual element value and pids
   // are caputured
   // Test to see we have an element value  
  if(isset($element_value) && $element_value != ''){

    // Test to see if we want this field
    foreach($capture_fields as $field){
      $has_field = strpos($path, $field);
    }    
    //Here we have data and want to capture
    if($has_field == 1){
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
      $results[$element] = array('count' => 1, 'attributes' => array(), 'children' => array());
    }

return;

}





/*
 * @params $simpleXMLIterator, $resultsArray
 *
 * processElement - Add element to array
 * 
 * test for attributes and add them to results array
 *
 * Test for children and recurse using this function
 */ 
function processDocument($sxe, &$results){

  for ($sxe->rewind(); $sxe->valid(); $sxe->next()) {

    processElement($sxe->key(), $results);

    //Get the attributes and process if they exits
    $attrs = (array)$sxe->current()->attributes();
    if(array_key_exists('@attributes', $attrs)){
     processAttributes($attrs, $results[$sxe->key()]['attributes']);
    }

    //Now lets think of the children
    if ($sxe->hasChildren()) {
      $results[$sxe->key()]['children'] = array();
      processDocument($sxe->current(), $results[$sxe->key()]['children']);
    }
  }
return;
}


function processElement($element, &$results){

    //The key exists
    if(array_key_exists($element, $results)){
      //increment count
      $results[$element]['count']++;
    }else{
      $results[$element] = array('count' => 1, 'attributes' => array(), 'children' => array());
    }

return;

}


//Add element attributes to the attributes array
function processAttributes($attributes, &$attribute_array){
  foreach($attributes['@attributes'] as $k => $v){
     $kv = $k . " : " . $v;
     if(array_key_exists($kv, $attribute_array)){
      $attribute_array[$kv]++;
    }else{
      $attribute_array[$kv] = 1;
    }
  }
}