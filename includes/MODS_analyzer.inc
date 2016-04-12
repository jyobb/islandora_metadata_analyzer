<?php

/* @params fedora_object, results container, data container, params
 *
 * Grab the datastream, load it into a simpleXMLInterator, call processor 
 *
 */
function islandora_MODS_metadata_analyzer($object, &$results, &$data, &$params, &$path_data){

$datastream = $object['MODS']->content;
//$xml = simplexml_load_string($datastream, null, null, 'mods', true);
$sxe = simplexml_load_string($datastream, 'SimpleXMLIterator');
module_load_include('inc', 'islandora_metadata_analyzer', 'includes/processors');
$params['stream_root'] = '/mods/';
processDocument($sxe, $object->id, $results, $data, '/mods', $params, $path_data);

return;

}


