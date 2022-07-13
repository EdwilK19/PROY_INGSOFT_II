<?php

include'conexion.php';

if ($con) {
    echo "Conexion con base de datos exitosa! ";

    if(isset($_POST['valoruv'])) {
        $valoruv = $_POST['valoruv'];
        echo "Registro Rayos UV";
        echo "Valor de Sensor: ".$valoruv;
        date_default_timezone_set('america/bogota');
        $fecha = date("Y-m-d");

        $consulta = "INSERT INTO marco(valorsensor,fecha) VALUES ('$valoruv', '$fecha')";
       // $consulta = "UPDATE ESP32 SET ESpO2='$ESpO2',BMP='$BPM' WHERE Id = 1";
        $resultado = mysqli_query($con, $consulta);
        if ($resultado){
            echo " Registo en base de datos OK! ";
        } else {
            echo " Falla! Registro BD";
        }
    }


} else {
    echo "Falla! conexion con Base de datos ";
}


?>
