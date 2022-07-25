<?php
include './connect.php';

$connect = mysqli_connect($hostname, $username, $password, $database);
$query = "select * from mod_temperatura order by id DESC LIMIT 1 ";
$results = mysqli_query($connect, $query);

if($data=mysqli_fetch_array($results)){
    $result=$data["temperatura"];}

mysqli_close($connect);
echo ($result);