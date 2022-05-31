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

echo $response;

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

<!doctype html>
<html>
<head>
<title>Forecast Weather using OpenWeatherMap with PHP</title>
</head>
<body>
    <div class="report-container">
        <h2><?php echo $data->name; ?> Weather Status</h2>
        <div class="time">
            <div><?php echo date("l jS F", $currentTime); ?></div>
            <div><?php echo ucwords($data->weather[0]->description); ?></div>
        </div>
        <div class="weather-forecast">
            <img
                src="http://openweathermap.org/img/w/<?php echo $data->weather[0]->icon; ?>.png"
                class="weather-icon" /> 
                <?php echo $data->main->temp; ?>°C<br>
                <?php echo $data->main->temp_max; ?>°C<br>
                
                <span
                class="min-temperature"><?php echo $data->main->temp_min; ?>°C</span>
        </div>
        <div class="time">
            <div>Humidity: <?php echo $data->main->humidity; ?> %</div>
            <div>Wind: <?php echo $data->wind->speed; ?> km/h</div>
            <div>Sunrise: <?php echo $sunrise ?></div>
            <div>Sunset: <?php echo $sunset ?></div>
        </div>
    </div>
</body>
</html>