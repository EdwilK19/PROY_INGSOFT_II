<?php

include './connect.php';
$json=array();

$connect = mysqli_connect($hostname, $username, $password, $database);
$query = "select * from mod_temperatura order by id DESC LIMIT 1 ";
$results = mysqli_query($connect, $query);
    
if($data=mysqli_fetch_array($results)){
    $result["temperatura"]=$data['temperatura'];
    $result["fechaT"]=$data['fecha'];
    $json=$result;
}else{
    $result["temperatura"]='0';
    $result["fecha"]='0';
    $json=$result;
}

mysqli_close($connect);
echo json_encode($json);