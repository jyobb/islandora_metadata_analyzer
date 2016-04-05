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
function islandora_metadata_analyzer_search_replace($params){

  $stream = $params['stream']; 
  $path = $params['path'];
  $old_data = $params['old_data'];
  $new_data = $params['new_data'];
  $pid_list = explode(',',$params['pid_list']);
  $path_parts = explode("@", $path);

  foreach ($pid_list as $pid) {
    $fedoraObject = islandora_object_load($pid);

    if($stream == 'DC'){

      $dc = $fedoraObject['DC']->content;
      $xml = simplexml_load_string($dc, "SimpleXMLElement", null, 'dc', true);

    }elseif($stream == 'MODS'){
      $datastream = $fedoraObject['MODS']->content;
      $dom = new DOMDocument();
      $xml = $dom->loadXML($datastream);	   
      if(!$xml){
        //drupal error message
      }
    }else{
      drupal_set_message("The " . $stream . " datastream was not found");
    }

    //Find the namesapces
    $xpath = new DOMXPath($dom);
    $result = $xpath->query("//namespace::*");
    $prefix = '';
    foreach($result as $node) {
      if(strcasecmp($node->localName, $stream) == 0 ){
        $prefix = $node->localName;
        $namespace = $node->nodeValue;        
        break;
      }
    }
 
    //Test for prefix
    //Find the nodes
    $nodeXPath = new DOMXPath($dom);
    $nodeXPath->registerNamespace($prefix, $namespace);    
    
    //Build xpath qeury string
    $base_path = '/mods' . $path_parts[0];
    $xpathPath = str_replace("/", "/" . $prefix . ":", $base_path);
    
    //Perform query
    $elements = $nodeXPath->query($xpathPath);
    if(!is_null($elements)){
      foreach($elements as $element){
          if(strcmp($element->nodeValue, $old_data) == 0){
            $element->nodeValue = $new_data;
            dpm($element->nodeValue);
          }
       }
    }
    dpm($dom->saveXML());
  }  
return;
}