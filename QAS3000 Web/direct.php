<!DOCTYPE html>
<html lang="fr">
        <head>
                <meta charset="utf-8">
        <title>Page d'accueil</title>
        <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.3/jquery.min.js"></script>
        </head>
        <body>
        <h1>CAPTEURS</h1>
                <?php
                $mysqli = new mysqli("localhost", "simon", "projet2022", "QAS3000");
                $mysqli->set_charset("utf8");
        
                $requete = "SELECT * FROM CAPTEURS ORDER BY id DESC LIMIT 0, 1";
                $resultat = $mysqli->query($requete);
                $ligne = $resultat->fetch_assoc();
                echo ' Température : ' . $ligne['temp'] . ' °C <br> Humidité : ' . $ligne['hum'] . '% <br> CO2 : ' . $ligne['co2'] . '<br> GAZ Global :' . $ligne['aq'] . '<br>';
                
                $mysqli->close();
                ?>


        <script type="text/javascript">
    function loadlink(){
    $('#links').load('test.php',function () {
         $(this).unwrap();
    });
}

loadlink(); // This will run on page load
setInterval(function(){
    loadlink() // this will run after every 5 seconds
}, 5000);
</script>
    </body> 
</html>


