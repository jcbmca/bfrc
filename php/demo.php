/*
https://www.sitepoint.com/simple-captchas-php-gd/
*/

<?php
session_start();
$_SESSION['count'] = time();
$image;
?>

<title>demo.php</title>

<body style="background-color:#ddd; ">

    <?php
    $flag = 5;
    if (isset($_POST["flag"])) {
        $input = $_POST["input"];
        $flag = $_POST["flag"];
    }

    if ($flag == 1) {
        if ($input == $_SESSION['captcha_string']) {
    ?>

            <div style="text-align:center;">
                <h1>Your answer is correct!</h1>

                <form action=" <?php echo $_SERVER['PHP_SELF']; ?>" method="POST">
                    <input type="submit" value="refresh the page">
                </form>
            </div>

        <?php

        } else {
        ?>

            <div style="text-align:center;">
                <h1>Your answer is incorrect!<br>please try again </h1>
            </div>

        <?php
            create_image();
            display();
        }
    } else {
        create_image();
        display();
    }

    function display()
    {
        ?>

        <div style="text-align:center;">
            <h3>TYPE THE TEXT YOU SEE IN THE IMAGE</h3>
            <b>This is just to check if you are a robot</b>

            <div style="display:block;margin-bottom:20px;margin-top:20px;">
                <img id="image" src="image<?php echo $_SESSION['count'] ?>.png">
            </div>
            <form action=" <?php echo $_SERVER['PHP_SELF']; ?>" method="POST" />
            <input type="text" name="input" />
            <input type="hidden" name="flag" value="1" />
            <input type="submit" value="submit" name="submit" />
            </form>

            <form action=" <?php echo $_SERVER['PHP_SELF']; ?>" method="POST">
                <input type="submit" value="refresh the page">
            </form>
        </div>

    <?php
    }

    function  create_image()
    {
        $_count_pixel = 150; // 1000;
        $_count_lines = 3;
        $_length = 1; // 6
        $_height = 50;
        $_width =  25; // 200

        global $image;
        $image = imagecreatetruecolor( $_width, 50 ) or die("Cannot Initialize new GD image stream");

        $background_color = imagecolorallocate( $image, 255, 255, 255);
        $text_color = imagecolorallocate($image, 0, 255, 255);
        $line_color = imagecolorallocate($image, 64, 64, 64);
        $pixel_color = imagecolorallocate($image, 0, 0, 255);

        imagefilledrectangle($image, 0, 0, $_width, $_height, $background_color);

        // agrega las 3 lineas
       /*
        for ($i = 0; $i < $_count_lines; $i++) 
        {
            imageline($image, 0, rand() % $_height, $_width, rand() % $_height, $line_color);
        }
       */
         /*
        // agrega los pixeles de color (1000)
        for ($i = 0; $i < $_count_pixel; $i++) 
        {
            imagesetpixel($image, rand() % $_width, rand() % $_height, $pixel_color);
        }
           */

        $letters = '0123456789'; // '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'; //
        $len = strlen($letters);
        $letter = $letters[rand(0, $len - 1)];

        $text_color = imagecolorallocate($image, 0, 0, 0);
        $word = "";


        for ($i = 0; $i < $_length; $i++) 
        {
            $letter = $letters[rand(0, $len - 1)];
            imagestring($image, 7, 5 + ($i * 30), 20, $letter, $text_color);
            //imagettftext($image, 20, 0, 11, 21, $text_color, $font, $letter);
            $word .= $letter;
        }
        $_SESSION['captcha_string'] = $word;

        $images = glob("*.png");
        foreach ($images as $image_to_delete) 
        {
            @unlink($image_to_delete);
        }
        imagepng($image, "image" . $_SESSION['count'] . ".png");
    }

    ?>
</body>