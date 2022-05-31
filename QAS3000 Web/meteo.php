<?php
$apiKey = "3a13269bafd9ee9dbb3e2cc9da72e3b2";
$cityId = "6452047";
$googleApiUrl = "http://api.openweathermap.org/data/2.5/weather?id=" . $cityId . "&lang=en&units=metric&APPID=" . $apiKey;

$ch = curl_init();

curl_setopt($ch, CURLOPT_HEADER, 0);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_URL, $googleApiUrl);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
curl_setopt($ch, CURLOPT_VERBOSE, 0);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
$response = curl_exec($ch);

curl_close($ch);
$data = json_decode($response);
$currentTime = time();

$uep=$data->sys->sunrise;
$t = date('r',$uep);
$savedtime = $t;
$servertime = ini_get('date.timezone');
$time = strtotime($savedtime . $servertime);
$sunrise = date("H:i", $time);

$uep2=$data->sys->sunset;
$t2 = date('r',$uep2);
$savedtime2 = $t2;
$servertime2 = ini_get('date.timezone');
$time2 = strtotime($savedtime2 . $servertime2);
$sunset = date("H:i", $time2);

?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Météo</title>
  <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,400,600,700&display=swap" rel="stylesheet">
  <link href="https://cdn.jsdelivr.net/npm/remixicon@2.5.0/fonts/remixicon.css" rel="stylesheet">

  <link href="site.css" rel="stylesheet">
</head>
<body>
  <header class="header" id="header">
    <nav class="nav container">
        <a href="#" class="nav__logo">
            <i class="ri-leaf-fill nav__logo-icon"></i> QAS3000
        </a>
        <div class="nav__menu" id="nav-menu">
            <ul class="nav__list">
                <li class="nav__item">
                    <a href="index.html" class="nav__link">Accueil</a>
                </li>
                <li class="nav__item">
                    <a href="salle.html" class="nav__link">Salles</a>
                </li>
                <li class="nav__item">
                    <a href="meteo.php" class="nav__link active-link">Metéo</a>
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
<main class="main-container">

  <div class="location-and-date">
    <h1 class="location-and-date__location">Argenteuil, France</h1>
    <div><?php echo date("l jS F", $currentTime); ?></div>
  </div>


  <div class="current-temperature">
    <div class="current-temperature__icon-container">
      <img src="icons/mostly-sunny.svg" class="current-temperature__icon" alt="">
    </div>
    <div class="current-temperature__content-container">
      <div class="current-temperature__value"><?php echo $data->main->temp; ?>°<br></div>
      <div class="current-temperature__summary"><?php echo $data->weather[0]->description; ?></div>
    </div>
  </div>


  <div class="current-stats">
    <div>
      <div class="current-stats__value"><?php echo $data->main->temp_max; ?>&deg;</div>
      <div class="current-stats__label">Max</div>
      <div class="current-stats__value"><?php echo $data->main->temp_min; ?>&deg;</div>
      <div class="current-stats__label">Min</div>
    </div>
    <div>
      <div class="current-stats__value"><?php echo $data->wind->speed; ?> km/h</div>
      <div class="current-stats__label">Vent</div>
      <div class="current-stats__value"><?php echo $data->main->humidity; ?> %</div>
      <div class="current-stats__label">Humidité</div>
    </div>
    <div>
      <div class="current-stats__value"><?php echo $sunrise ?></div>
      <div class="current-stats__label">Lever du soleil</div>
      <div class="current-stats__value"><?php echo $sunset ?></div>
      <div class="current-stats__label">Coucher du soleil</div>
    </div>
  </div>

</main>

</body>
</html>