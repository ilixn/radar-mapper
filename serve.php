<?php
echo $_POST['coords'];
echo $_GET['coords'];

echo exec('python radar.py ' . $_GET['coords']);
?>
