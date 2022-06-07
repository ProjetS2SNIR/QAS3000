<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">

        <!-- ===== CSS ===== -->
        <link rel="stylesheet" href="assets/css/styles.css">
    
        <!-- ===== BOX ICONS ===== -->
        <link href='https://cdn.jsdelivr.net/npm/boxicons@2.0.5/css/boxicons.min.css' rel='stylesheet'>

        <title> Connectez vous au site QAS3000 </title>
    </head>
    <body>
        <div class="login">
            <div class="login__content">
                <div class="login__img">
                    <img src="assets/img/img-login.svg" alt="">
                </div>

                <div class="login__forms">
                    <form action="verification.php" method="POST" class="login__registre" id="login-in">
                        <h1 class="login__title">Connexion page admin</h1>
    
                        <div class="login__box">
                            <i class='bx bx-user login__icon'></i>
                            <input type="text" placeholder="Utilisateur" name="username" class="login__input">
                        </div>
    
                        <div class="login__box">
                            <i class='bx bx-lock-alt login__icon'></i>
                            <input type="password" placeholder="Mot de passe" name="password" class="login__input">
                        </div>

                         <input type="submit" id='submit' value='Se connecter'class="login__button" >
                        <div>
                            <span class="login__account">Le projet ?</span>
                            <span class="login__signin" id="sign-up">QAS 3000</span>
                        </div>
                    </form>

                    <form action="" class="login__create none" id="login-up">
                        <h1 class="login__title">QAS3000</h1>
                        <p>Notre projet consiste en la création d’un système de surveillance de la qualité de l’air dans une salle qui nous permettra d’ouvrir ou fermer les fenêtres en fonction de la température, de l’humidité et du CO2 contenu dans l’air d’une salle du lycée Jean Jaurès. Les valeurs obtenues issues de capteurs seront enregistrées puis utilisées pour ouvrir ou fermer les fenêtres si le seuil mise en place a été atteint. </p>
                        <div>
                            <span class="login__account">Vous voulez accèder à l'interface admin ?</span><br>
                            <span class="login__signup" id="sign-in">Connexion</span>
                        </div>

                        <!-- <div class="login__social">
                            <a href="#" class="login__social-icon"><i class='bx bxl-facebook' ></i></a>
                            <a href="#" class="login__social-icon"><i class='bx bxl-twitter' ></i></a>
                            <a href="#" class="login__social-icon"><i class='bx bxl-google' ></i></a>
                        </div>-->
                    </form>
                </div>
            </div>
        </div>

        <!--===== MAIN JS =====-->
        <script src="assets/js/main.js"></script>
    </body>
</html>
