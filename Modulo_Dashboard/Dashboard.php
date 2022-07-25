<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />
<meta name="description" content="" />
<meta name="author" content="" />
<title>Sistema de Monitoreo</title>
<link href="https://cdn.jsdelivr.net/npm/simple-datatables@latest/dist/style.css" rel="stylesheet" />
<link href="rcs/css/styles.css" rel="stylesheet" />
<link href="css/style.css" rel="stylesheet"/>
<link href="css/bootstrap-grid.min.css" rel="stylesheet"/>
<script src="https://use.fontawesome.com/releases/v6.1.0/js/all.js" crossorigin="anonymous"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js"></script>
<link rel="shortcut icon" href="favicon.png" />

</head>
<body class="sb-nav-fixed">
<nav class="sb-topnav navbar navbar-expand navbar-dark bg-dark"> <a class="navbar-brand ps-3" href="Dashboard.php">DASHBOARD</a>
  <button class="btn btn-link btn-sm order-1 order-lg-0 me-4 me-lg-0" id="sidebarToggle" href="#!"><i class="fas fa-bars"></i></button>
  <form class="d-none d-md-inline-block form-inline ms-auto me-0 me-md-3 my-2 my-md-0">
  </form>
  <ul class="navbar-nav ms-auto ms-md-0 me-3 me-lg-4">
    <li class="nav-item dropdown"> <a class="nav-link dropdown-toggle" id="navbarDropdown" href="#" role="button" data-bs-toggle="dropdown" aria-expanded="false"><i class="fas fa-user fa-fw"></i></a>
      <ul class="dropdown-menu dropdown-menu-end" aria-labelledby="navbarDropdown">
        <li><a class="dropdown-item" href="index.php">SALIR</a></li>
      </ul>
    </li>
  </ul>
</nav>
<div id="layoutSidenav">
  <div id="layoutSidenav_nav">
    <nav class="sb-sidenav accordion sb-sidenav-dark" id="sidenavAccordion">
      <div class="sb-sidenav-menu">
        <div class="nav">
          <div class="sb-sidenav-menu-heading">MENÚ</div>
          <a class="nav-link" href="Dashboard.php">
          <div class="sb-nav-link-icon"><i class="fas fa-tachometer-alt"></i></div>
          MONITOREO </a>
			<a class="nav-link" href="">
          <div class="sb-nav-link-icon"><i class="fas fa-tachometer-alt"></i></div>
          TRAZABILIDAD</a>
		  </div>
      </div>
    </nav>
  </div>
  <div id="layoutSidenav_content">
    <main>
      <div class="container-fluid px-4">
        <h1 class="mt-4">MONITOREO&nbsp;</h1>
        <ol class="breadcrumb mb-4">
          <li class="breadcrumb-item active">Panel de control principal</li>
        </ol>
        <div class="container-fluid px-1">
          <div class="row">
            <div class="col-lg-3 col-md-11">
              <div class="card">
                <h3>TEMPERATURA</h3>
                <div class="card-content">
                  <div class="gauge-temperature GaugeMeter gaugeMeter temperatura"  data-theme="blue" data-width="16"  data-style="Arch" data-animationstep="0">
                    <p class="value-temperatura">0 C°</p>
                  </div>
                </div>
                <div class="value-fechaT text-content">Ultima Consulta: </div>
              </div>
              <br>
            </div>
            <div class="col-lg-3 col-md-5">
              <div class="card">
                <h3>HUMEDAD</h3>
                <div class="card-content">
                  <div class="gauge-humidity gaugeMeter humedad" data-theme="green" data-width="16"  data-style="Arch" data-animationstep="0">
                    <p class="value-humidity">0 %</p>
                  </div>
                </div>
                <div class="value-fechaH text-content">Ultima Consulta: </div>
              </div>
            </div>
            <div class="col-lg-3 col-md-5">
              <div class="card">
                <h3>ILUMINACIÓN</h3>
                <div class="card-content">
                  <div class="gauge-iluminacion GaugeMeter gaugeMeter iluminacion" data-theme="DarkGold-LightGold" data-width="16"  data-style="Arch" data-animationstep="0">
                    <p class="value-iluminacion">0 C°</p>
                  </div>
                </div>
                <div class="value-fechaI text-content">Ultima Consulta: </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </main>
    <footer class="py-4 bg-light mt-auto">
      <div class="container-fluid px-4">
        <div class="d-flex align-items-center justify-content-between small">
          <div class="text-muted">Copyright &copy; GRUPO 2IL141</div>
        </div>
      </div>
    </footer>
  </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" crossorigin="anonymous"></script> 
<script src="rcs/js/scripts.js"></script> 
<script src="https://cdn.jsdelivr.net/npm/simple-datatables@latest" crossorigin="anonymous"></script> 
<script src="rcs/js/datatables-simple-demo.js"></script> 
<script type='text/javascript' src="js/jquery-3.5.1.min.js"></script> 
<script type='text/javascript' src="js/gauge-meter.js"></script> 
<script>
    $(document).ready(function () {

       setInterval(charts, 1500);

    });

    function charts(){

        $.ajax({
            url:"http://localhost/dashprueba/backend/getData.php",
            type:"POST",
            dataType:"json",
            success:function(data){
                
                $(".gauge-temperature").gaugeMeter({ percent: data.temperatura*100/50});
                $(".value-temperatura").html(data.temperatura+" °C");
				        $(".value-fechaT").html("Última Consulta: " +data.fechaT);


            }
        });
		
		$.ajax({
			url:"http://localhost/dashprueba/backend/getHumedad.php",
            type:"POST",
            dataType:"json",
            success:function(data){


                $(".gauge-humidity").gaugeMeter({ percent: data.humedad});
                $(".value-humidity").html(data.humedad+" %")
                $(".value-fechaH").html("Última Consulta: " +data.fechaH);

            }
        });

    $.ajax({
			url:"http://localhost/dashprueba/backend/getiluminacion.php",
            type:"POST",
            dataType:"json",
            success:function(data){
              

                $(".gauge-iluminacion").gaugeMeter({ percent: data.iluminacion});
                $(".value-iluminacion").html(data.iluminacion+" %")
                $(".value-fechaI").html("Última Consulta: " +data.fechaI);

            }
        });

    }

</script>
</body>
	
<script>
  function showHint(str, str2) {
      alert(str + str2)
    const xhttp = new XMLHttpRequest();
    xhttp.onload = function() {
        document.getElementById("txt1").value = "";
      document.getElementById("txt2").value = "";
    }
    xhttp.open("GET", "gethint.php?q="+str+"&r="+str2,true);
    xhttp.send();
  }
  </script>
	
</html>