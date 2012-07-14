<?php
class ViewingAngle
{
  public $view;

  public function __construct() {
  }

  public function update($str) {
    $str = str_replace('{', '', $str);
    $str = str_replace('}', '', $str);
    $c = explode(',', $str);
    $this->view = array();
    foreach ($c as $box) {
      $this->view[] = explode(' ', trim($box));
    }
  }

  public function getElementsAt($nb) {
    if (isset($this->view[$nb]))
      return $this->view[$nb];
    return false;
  }

  public function findClosest($item) {
    $i = 0;
    while (isset($this->view[$i]))
      {
	if (in_array($item, $this->view[$i]) === true)
	  return $i;
	$i++;
      }
    return -1;
  }

  public function getSight() {
    $i = 0;
    while (isset($this->view[$i]))
      $i++;
    $i--;
    switch ($i) {
    case 0:
      return 0;
    case ($i <= 3):
      return 1;
    case ($i <= 8):
      return 2;
    case ($i <= 15):
      return 3;
    case ($i <= 24):
      return 4;
    case ($i <= 35):
      return 5;
    case ($i <= 48):
      return 6;
    case ($i <= 63):
      return 7;
    case ($i <= 80):
      return 8;
    }
    return 1;
  }
}
?>