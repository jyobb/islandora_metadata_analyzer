<?php

function islandora_DC_metadata_analyzer($object, &$results){

$dc = $object['DC']->content;
$sxe = simplexml_load_string($dc, "SimpleXMLIterator", null, 'dc', true);
module_load_include('inc', 'islandora_metadata_analyzer', 'includes/processors');
processDocument($sxe, $results);

return;

}

