<?php

  

?>

<h3><?php echo "Test Title: ". $variables['title']; ?></h3>
<h3><?php echo "Metadata Stream: " . $variables['stream']; ?></h3>
<h3><?php echo "PID of Collection: " . $variables['pid']; ?></h3>
<h3><?php echo "Time to Query: " . $variables['query_time']; ?></h3>
<h3><?php echo "Records Processed: " . $variables['record_count']; ?></h3>




<div id="resultblock">
<?php 
foreach( $variables['countArray'] as $all_paths) {

  $link = l(t('View PIDS'), 'islandora_metadata_analyzer/ajax-allpath/nojs/' . $all_paths['path_id'], array('attributes' => array('class' => array('use-ajax'))));
  $downloadlink = l(t('Download PIDS'), 'islandora_metadata_analyzer/piddownloads/' . $all_paths['path_id'] );

  $missinglink = l(t('View Missing PIDS'), 'islandora_metadata_analyzer/ajax-allpathmissing/nojs/' . $all_paths['path_id'], array('attributes' => array('class' => array('use-ajax'))));

  $downloadmissinglink = l(t('Download PIDS'), 'islandora_metadata_analyzer/piddownloads/' . $all_paths['path_id'] );
  
  echo '<div class="allpath-container">';
  echo '<div class="path-highlight">' . $all_paths['path'] . '  Total found: ' . $all_paths['count'] .' | ' . $link . ' | '. $downloadlink . ' | '. $missinglink . ' | '. $downloadmissinglink . '</div><div id="allpathpids-' . $all_paths['path_id'] . '"></div><div id="missingallpathpids-' . $all_paths['path_id'] . '"></div>';
  echo '</div>';

} 
?>
</div>

<div id="capturedblock">
<h3>Fields with Captured Data</h3>
<?php

foreach( $variables['path_data'] as $path ){

  $link = l(t($path['path']), 'islandora_metadata_analyzer/ajax-path/nojs/' . $path['path_id'], array('attributes' => array('class' => array('use-ajax'))));
  echo '<div class="path-container">';
  echo '<div class="path-' . $path['path_id'] . '">' . $link. '</div><div id="pathdata-' . $path['path_id'] . '"></div>';
echo '</div>'; 
}
?>

</div>



<?php 

  /* Talk to Tim before removing

function getElement($k, &$element, &$out, $d){

  $out .= '<div class="elem-' . $d .'"><div class="elem-elem">' . $k . '</div><div class="elem-sub"><div id="count-' . $d .'">Count: ' . $element['count'] . '</div>';

  if(!empty($element['attributes'])){
    doAttributes($k, $element['attributes'], $out, $d);
    }
  if(!empty($element['children'])){
    ++$d;

    foreach($element['children'] as $ck => $cv){      
      getElement($ck, $cv, $out, $d);
    }
  }
  $out .= '</div></div>';
}

function doAttributes($element, &$attributes, &$out, $d) {
  foreach($attributes as $name => $count){
    $out .= '<div class="attr-'. $element . '-' . $d . '">Attribute: ' . $name . ': ' . $count . '</div>'; 
  }
}
  */


?>