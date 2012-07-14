#!/bin/env php
<?php
error_reporting(0);
require_once('ZappyNET.class.php');

  /*
   ** Script start
   */

function getoptions()
{
  global $argv;

  $opts = getopt('n:p:h:');
  if (empty($opts['n']) || empty($opts['p'])) {
    echo "USAGE : ". $argv[0]." -n team -p port [-h host]\n";
    exit(1);
  }
  if (empty($opts['h']))
    $opts['h'] = 'localhost';
  return $opts;
}

$opts = getoptions();

try {
  $t = new ZappyNET($opts);
}
catch (Exception $e) {
  echo 'Error : '.$e->getMessage()."\n";
  exit(1);
}

$t->setCallback("update");
$t->monitor(0);
$status;
pcntl_wait($status);
?>
