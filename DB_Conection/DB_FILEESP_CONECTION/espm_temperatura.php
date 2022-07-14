<?php

include'conexion.php';

if ($con) {
    echo "Conexion con base de datos exitosa! ";

    if(isset($_POST['temperatura'])) {
        $temperatura = $_POST['temperatura'];
        echo "Registro de Temperatura";
        echo "Valor de Sensor: ".$temperatura;
        date_default_timezone_set('america/bogota');
        $fecha = date("Y-m-d");

        $consulta = "INSERT INTO mod_temperatura(temperatura,fecha) VALUES ('$temperatura', '$fecha')";
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
