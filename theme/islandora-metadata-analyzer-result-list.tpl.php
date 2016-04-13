<?php


  //dpm($variables);
?>


<?php foreach( $variables['resultArray'] as $id => $name ){ ?>
    <p><a href="elementCount/<?php echo $id;?>"><?php echo $name; ?></a><a href="deleteResult/<?php echo $id;?>"><?php echo " | Delete: " . $name; ?></a></p>
<?php } 


?>