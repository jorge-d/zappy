<?php
Class Moves
{
  private $c;
  
  public function __construct($connect) {
    $this->c = $connect;
  }

  private function getLine($spot) {
    switch ($spot) {
    case -1:
      return 0;
    case 0:
      return 0;
    case ($spot <= 3):
      return 1;
    case ($spot <= 8):
      return 2;
    case ($spot <= 15):
      return 3;
    case ($spot <= 24):
      return 4;
    case ($spot <= 35):
      return 5;
    case ($spot <= 48):
      return 6;
    case ($spot <= 63):
      return 7;
    case ($spot <= 80):
      return 8;
    }
  }

  private function selectDirection($spot, $line) {
    if ($spot == 2 || $spot == 6 || $spot == 12 || $spot == 20
	|| $spot == 30 || $spot == 42 || $spot == 56 || $spot == 72)
      return;
    else if (($line == 1 && $spot < 2)
	     || ($line == 2 && $spot < 6)
	     || ($line == 3 && $spot < 12)
	     || ($line == 4 && $spot < 20)
	     || ($line == 5 && $spot < 30)
	     || ($line == 6 && $spot < 42)
	     || ($line == 7 && $spot < 56)
	     || ($line == 8 && $spot < 72))
      $this->c->gauche();
    else
      $this->c->droite();
  }

  public function moveTo($item) {
    $this->c->state = "moveTo " . $item;
    $spot = $this->c->view->findClosest($item);
    if ($spot == -1)
      {
	$r = rand(0,10);
	if ($r == 1)
	  $this->c->gauche();
	else if ($r == 5)
	  $this->c->droite();
	else
	  $this->c->avance();
	$this->c->voir();
	$this->c->replies->push("ko");
	return;
      }
    $line = $this->getLine($spot);
    for ($i = 0; $i < $line; $i++) {
      $this->c->avance();
      $this->c->wait--;
    }
    $this->selectDirection($spot, $line);
    $this->c->voir();
    $this->c->replies->push("ok");
  }

  public function gatherStone($stone) {
    $this->c->state = "gatherStone";
    $spot = $this->c->view->findClosest($stone);
    if ($spot == -1)
      {
	$this->c->avance();
	$this->c->voir();
	$this->c->replies->push("ko");
	return;
      }
    $line = $this->getLine($spot);
    for ($i = 0; $i < $line; $i++) {
      $this->c->avance();
    }
    $this->selectDirection($spot, $line);
    $this->c->voir();
    $this->c->replies->push($stone);
  }

  public function travelTo() {
    static $i = 0;
    $this->c->state = "travelTo";
    if ($this->c->inventory["nourriture"] <= 6 && sizeof($this->c->targets) == 0)
      {
	$fset = array("nourriture" => 0);
	$floor = array_merge($fset, array_count_values($this->c->view->getElementsAt(0)));
    	if ($floor["nourriture"] > 0)
    	  {
    	    $this->c->prendObjet("nourriture");
    	    $this->c->state = "travelTo";
    	  }
    	else
	  {
	    $this->c->replies->push("food");
	    $this->c->job = "Gatherer";
	  }
    	$this->c->voir();
    	return;
      }
    if (sizeof($this->c->targets) > 0)
      {
	foreach ($this->c->targets as $target) {
	  $this->c->broadcast($target . " come here");
	  $this->wait++;
	}
	$this->wait--;
      }
    else
      {
	if ($this->c->target == -1)
	  {
	    $this->c->job = "Gatherer";
	    $this->c->replies->push("ko");
	    return;
	  }
	$this->c->broadcast($this->c->target . " come here");
      }
    if (($this->c->target > $this->c->id && $this->c->target != -1)
	|| (sizeof($this->c->targets) == 0 && $this->c->level >= 4))
      $this->c->voir();
    $this->c->inventaire();
    $this->c->voir();
  }

  public function playerCount() {
    $fset = array("joueur" => 0);
    $floor = array_merge($fset, array_count_values($this->c->view->getElementsAt(0)));
    switch ($this->c->level) {
    case 1:
      if ($floor["joueur"] == 1)
	return true;
      return false;
    case 2:
      if ($floor["joueur"] == 2)
	return true;
      return false;
    case 3:
      if ($floor["joueur"] == 2)
	return true;
      return false;
    case 4:
      if ($floor["joueur"] == 4)
	return true;
      return false;
    case 5:
      if ($floor["joueur"] == 4)
	return true;
      return false;
    case 6:
      if ($floor["joueur"] == 6)
	return true;
      return false;
    case 7:
      if ($floor["joueur"] == 6)
	return true;
      return false;
    }
    return false;
  }

  public function goToMeeting() {
    static $i = 0;
    static $dance = array();
    $flag = 0;
    $this->c->state = "goToMeeting";
    if (sizeof($this->c->targets) == 0)
      {
	$dset = array("gauche" => 0, "droite" => 0);
	$dancing = array_merge($dset, array_count_values($dance));
	if ($dancing["gauche"] >= 5)
	  {
	    $this->c->droite();
	    $dance = array();
	    $this->c->voir();
	    return;
	  }
	else if ($dancing["droite"] >= 5)
	  {
	    $this->c->gauche();
	    $dance = array();
	    $this->c->voir();
	    return;
	  }
	if ($this->c->lastk != -1 && $this->c->lastk != 0)
	  {
	    if ($this->c->lastk == 1 || $this->c->lastk == 2 || $this->c->lastk == 8)
	      $this->c->avance();
	    else if ($this->c->lastk == 6 || $this->c->lastk == 7)
	      {
		$this->c->droite();
		array_push($dance, "droite");
	      }
	    else if ($this->c->lastk == 3 || $this->c->lastk == 4)
	      {
		$this->c->gauche();
		array_push($dance, "gauche");
	      }
	    else
	      {
	      	$i = rand(1,2);
		if ($i == 1)
		  $this->c->gauche();
		else 
		  $this->c->droite();
	      }
	    $this->c->wait--;
	  }
	else if ($this->c->lastk == 0)
	  {
	    $set = array("joueur" => 0);
	    $floor = array_merge($set, array_count_values($this->c->view->getElementsAt(0)));
	    if (($floor["joueur"] >= 2 && $this->c->level < 4)
		|| (($floor["joueur"] >= 3) && ($this->c->level == 4 || $this->c->level == 5))
		|| (($floor["joueur"] >= 3) && ($this->c->level == 6 || $this->c->level == 7)))
	      {
		while ($this->c->replies->getSize() > 0)
		  $this->c->replies->pop();
		$this->c->replies->push("arrived");
		$this->c->job = "Incanter";
	      }
	    else
	      $this->c->replies->push("ok");
	    $this->lastk = -1;
	    $dance = array();
	  }
	else
	  $this->c->replies->push("ok");
      }
    else if ($this->playerCount() === true && sizeof($this->c->targets) > 0)
      {
	if ($i >= 3)
	  {
	    while ($this->c->replies->getSize() > 0)
	      $this->c->replies->pop();
	    $this->c->replies->push("arrived");
	    $this->c->job = "Incanter";
	    $this->lastk = -1;
	    $i = 0;
	  }
	else 
	  $i++;
	$flag = 1;
      }
    else
      $this->c->replies->push("ok");
    if ($flag == 0)
      $i = 0;
    $this->c->inventaire();
    $this->c->voir();
  }
}