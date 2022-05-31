<?php
	          	$mysqli = new mysqli("localhost", "simon", "projet2022", "QAS3000");
	          	$mysqli->set_charset("utf8");
        
		          $requete = ("SELECT CO2,TEMPT,HUMI_H,QUALITYQ FROM CO2,Temperature,Humidite,QualiteAir WHERE ID_CO2 = (SELECT COUNT(ID_CO2) + 2 from CO2) and ID_TEMP = (SELECT COUNT(ID_TEMP) - 1 from Temperature) and ID_HUMI = (SELECT COUNT(ID_HUMI) - 1 from Humidite) and ID_QA = (SELECT COUNT(ID_QA) - 1 from QualiteAir) and ID_HUMI = (SELECT COUNT(ID_HUMI) - 1 from Humidite) and ID_QA = (SELECT COUNT(ID_QA) - 1 from QualiteAir)");
   
	          	$resultat = $mysqli->query($requete);
             		 $ligne = $resultat->fetch_assoc();
                  $temp = $ligne['TEMPT'];
                  $humi = $ligne['HUMI_H'];
                  $co2 = $ligne['CO2'];
                  $qa = $ligne['QUALITYQ'];

              header("Refresh: 10");
    
	          	$mysqli->close();
		?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Weather App</title>
  <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,400,600,700&display=swap" rel="stylesheet">
  <link href="https://cdn.jsdelivr.net/npm/remixicon@2.5.0/fonts/remixicon.css" rel="stylesheet">

  <link href="site.css" rel="stylesheet">
  <link href="salle.css" rel="stylesheet">
</head>
<body>
 <form action="parametre.php" method="POST">
  <header class="header" id="header">
    <nav class="nav container">
        <a href="#" class="nav__logo">
            <i class="ri-leaf-fill nav__logo-icon"></i> QAS3000
        </a>
        <div class="nav__menu" id="nav-menu">
            <ul class="nav__list">
                <li class="nav__item">
                    <a href="accueil.html" class="nav__link">Accueil</a>
                </li>
                <li class="nav__item">
                    <a href="salle.html" class="nav__link active-link">Salles</a>
                </li>
                <li class="nav__item">
                    <a href="meteo.php" class="nav__link">Metéo</a>
                </li>
                <li class="nav__item">
                    <a href="parametre.html" class="nav__link">Paramètres</a>
                </li>
                <li class="nav__item">
                    <a href="index.php" class="nav__link deconnexion">Déconnexion</a>
                </li>
            </ul>
	       </div>	        
    </nav>

                        
</header>
<div class="left">
        <div class="content">
            <h1>Salle A031</h1>
           <img class="temp" src="./image/temperaturenoir.png"><a class="resultt"> <?php echo $temp . '°'; ?></a>
           <img class="humi" src="./image/humiditénoir.png"><a class="resulth"> <?php echo $humi; ?> % </a>
 	   <img class="co" src="./image/co2noir.png"><a class="resultc"> <?php echo $co2; ?> ppm </a>
 	   <img class="pm" src="./image/pm2.5noir.png"><a class="resultp"> <?php echo $qa; ?> ppm </a>
        </div>
        </div>
</body>
</html>