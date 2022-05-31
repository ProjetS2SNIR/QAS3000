<?php
// Informations d'identification
define('DB_SERVER', '127.0.0.1');
define('DB_USERNAME', 'simon');
define('DB_PASSWORD', 'projet2022');
define('DB_NAME', 'QAS3000');

$temp = $_POST["temp"];
$humi= $_POST["humi"];
$co2= $_POST["co2"];
$qualite= $_POST["quali"];

$initemp = "30";
$inihumi= "60";
$inico2= "450";
$iniqualite= "1000";

// Connexion à la base de données MySQL 
$conn = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);


// Attempt insert query execution
if(isset($_POST['valide'])) {
$sql = "INSERT INTO Seuil (temp_seuil, humi_seuil, co2_seuil, qualite_seuil) VALUES ($temp, $humi, $co2, $qualite)";
}
elseif(isset($_POST['initialise'])) {
$sql = "INSERT INTO Seuil (temp_seuil, humi_seuil, co2_seuil, qualite_seuil) VALUES ($initemp, $inihumi, $inico2, $iniqualite)";
}


if(mysqli_query($conn, $sql))
{
    header('Location: parametre.html');
} else{
    echo "\nERROR: Could not able to execute $sql " . mysqli_error($con);
}

// Close connection
mysqli_close($conn);
?>
