<?php

  //dpm($variables);
  //dpm($variables['countArray']);


?>

<h3><?php echo "Test Title: ". $variables['title']; ?></h3>
<h3><?php /*echo $variables['result_id']; */?></h3>
<h3><?php echo "PID of Collection: " . $variables['pid']; ?></h3>
<h3><?php echo "Time to Query: " . $variables['query_time']; ?></h3>
<h3><?php echo "Records Processed: " . $variables['record_count']; ?></h3>




<div id="resultblock">
<?php 
foreach( $variables['countArray'] as $k => $v) {
    $output =''; 
    getElement($k, $v, $output, 0);						      
  echo $output;  
} 
?>

</div>
<?php
  //$path_out = '';
foreach( $variables['path_data'] as $path ){

  $link = l(t($path['path']), 'islandora_metadata_analyzer/ajax-path/nojs/' . $path['path_id'], array('attributes' => array('class' => array('use-ajax'))));
echo '<div class="path-' . $path['path_id'] .'">' . $link. '</div><div id="pathdata-' . $path['path_id'] . '"></div>';
 
}


?>





<?php 

function getElement($k, &$element, &$out, $d){
  $out .= '<div class="elem-' . $d .'"><div class="elem-elem">' . $k . '</div><div class="elem-sub"><div id="count-' . $d .'">Count: ' . $element['count'] . '</div>';
  if(!empty($element['attributes'])){
    doAttributes($k, $element['attributes'], $out, $d);
    }
  if(!empty($element['children'])){
    ++$d;
    //$out .= '<div id="element-' . ++$d . '">';
    foreach($element['children'] as $ck => $cv){      
      getElement($ck, $cv, $out, $d);
    }
    //$out .= '</div>';
  }
  $out .= '</div></div>';
}

function doAttributes($element, &$attributes, &$out, $d) {
  foreach($attributes as $name => $count){
    $out .= '<div class="attr-'. $element . '-' . $d . '">Attribute: ' . $name . ': ' . $count . '</div>'; 
  }
}



?>