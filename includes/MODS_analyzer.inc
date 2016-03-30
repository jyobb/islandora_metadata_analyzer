<?php

function islandora_MODS_metadata_analyzer($object, &$results, &$data, &$params){

$datastream = $object['MODS']->content;

//$xml = simplexml_load_string($datastream, null, null, 'mods', true);

$sxe = simplexml_load_string($datastream, 'SimpleXMLIterator');
//$sxe = simplexml_load_string($dc, 'SimpleXMLIterator', null, 'dc', true);

module_load_include('inc', 'islandora_metadata_analyzer', 'includes/processors');

newprocessDocument($sxe, $object->id, $results, $data, NULL, $params);

return;

}


