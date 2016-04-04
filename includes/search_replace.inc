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


  //$base_path = "/" . $path_parts[0];
  $base_path = "/mods/subject/hierarchicalGeographic/citySection";
  foreach ($pid_list as $pid) {
    $fedoraObject = islandora_object_load($pid);

    if($stream == 'DC'){

      $dc = $fedoraObject['DC']->content;
      $xml = simplexml_load_string($dc, "SimpleXMLElement", null, 'dc', true);

    }elseif($stream == 'MODS'){

      $datastream = $fedoraObject['MODS']->content;
      $xml = simplexml_load_string($datastream);
    }else{
      drupal_set_message("The " . $stream . " datastream was not found");
    }

    dpm($xml->asXML());

    foreach($xml->getDocNamespaces() as $strPrefix => $strNamespace) {
      if(strcasecmp($stream, $strPrefix) == 0 ){
      dpm("found namespace");
       $xml->registerXPathNamespace($strPrefix,$strNamespace);
      }else{
        //put something here for missing namespace.
        //find namespace matching stream and add to xpath   
        //http://php.net/manual/en/simplexmlelement.xpath.php
      }
    }

    $bad_nodes = $xml->xpath($base_path);
    dpm($bad_nodes);    

  }
  
return;
}