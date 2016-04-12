<?php

/* @params fedora_object, results container, data container, params
 *
 * Grab the datastream, load it into a simpleXMLInterator, call processor 
 *
 */
function islandora_DC_metadata_analyzer($object, &$results, &$data, &$params, &$path_data){

$dc = $object['DC']->content;
$sxe = simplexml_load_string($dc, "SimpleXMLIterator", null, 'dc', true);
module_load_include('inc', 'islandora_metadata_analyzer', 'includes/processors');
$params['stream_root'] = '/dc/';
processDocument($sxe, $object->id, $results, $data, '/dc', $params, $path_data);
return;

}
