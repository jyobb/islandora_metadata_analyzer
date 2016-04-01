<?php


  //dpm($variables);
?>


<?php foreach( $variables['resultArray'] as $id => $name ){ ?>
    <p><a href="elementCount/<?php echo $id;?>"><?php echo $name; ?></a></p>

<?php } 


?>