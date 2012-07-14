<?php
require_once('Connect.class.php');
require_once('Drone.class.php');
require_once('Queue.class.php');

class ZappyIA
{
  private $init;
  private $replies;
  private $orders;
  private $team;
  private $funcs;
  private $reply;
  private $coords;
  private $clinb;
  private $vangle;
  private $drone;
  private $automatons;
  private $connect;

  public function __construct($team, $ord, $rep) {
    $this->init = 0;
    $this->team = $team;
    $this->orders = $ord;
    $this->replies = $rep;
    $this->connect = new Connect($this->orders, $this->replies);
    $this->drone = new Drone($this->connect);
  }

  /*
   ** Initialization functions
   */

  public function sendTeamName() {
    $this->connect->team = $this->team;
    $this->orders->push($this->team ."\n");
  }

  /*
   ** Called every second
   */

  private function firstUpdates() {
    if ($this->init == 0)
      {
	$this->sendTeamName();
	$this->init++;
      }
    else if ($this->init == 1 && $this->replies->getSize() >= 3)
      {
	$this->replies->pop();
	$this->clinb = $this->replies->pop();
	$this->coords = $this->replies->pop();
	$this->init++;
	$this->connect->clnb = $this->clinb;
	$this->connect->initial_clnb = $this->clinb;
	$coords = explode(" ", $this->coords);
	$this->connect->mapx = $coords[0];
	$this->connect->mapy = $coords[1];
      }
    else if ($this->init == 2)
      {
	$this->drone->automation();
	$this->init++;
      }
  }

  private function getBroadcasts() {
    if ($this->replies->getSize() > 0 && strstr($this->replies->peekNext(), "message") !== false)
      {
	$reply = $this->replies->pop();
	if ($this->connect->job == "Boss")
	  $this->connect->broadcasts->BossinterpretBroadcast($reply);
	else
	  $this->connect->broadcasts->RegularinterpretBroadcast($reply);
	return true;
      }
    else if ($this->replies->getSize() > 0 && strstr($this->replies->peekFront(), "message") !== false)
      {
	$reply = $this->replies->unpush();
	if ($this->connect->job == "Boss")
	  $this->connect->broadcasts->BossinterpretBroadcast($reply);
	else
	  $this->connect->broadcasts->RegularinterpretBroadcast($reply);
	return true;
      }
    return false;
  }

  private function getConnectNbr() {
    if ($this->replies->getSize() > 0 && ctype_digit($this->replies->peekNext()) !== false)
      {
	$reply = $this->replies->pop();
	$this->connect->clnb = $reply;
      }
    else if ($this->replies->getSize() > 0 && ctype_digit($this->replies->peekFront()) !== false)
      {
	$reply = $this->replies->unpush();
	$this->connect->clnb = $reply;
      }
  }

  public function update() {
    if ($this->getBroadcasts() === true)
      return;
    $this->getConnectNbr();
    if ($this->init <= 2)
      $this->firstUpdates();
    else if ($this->replies->getSize() > 0 && 
	     $this->connect->updates->waitForUpdate() === true)
      $this->connect->updates->updateViewOrInventory();
    else if (($this->replies->getSize() > 0
	      || $this->init == 3))
      {
	$this->drone->automation();
	$this->init++;
      }
  }
}
?>