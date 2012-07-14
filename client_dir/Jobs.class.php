<?php
class Jobs
{
  private $c;
  
  public function __construct($connect) {
    $this->c = $connect;
  }

  public function waitForJob() {
    static $i = 0;
    $this->c->state = "waitForJob";
    if (sizeof($this->c->team_id) >= 2 && $i == 4)
      {
	if (isset($this->c->team_id[0]) && $this->c->team_id[0] == $this->c->id)
	  $this->c->job = "Boss";
	else
	  $this->c->job = "Peon";
	$i = 0;
      }
    else if ($i == 5)
      {
	$this->c->job = "Boss";
	$i = 0;
      }
    if ($this->c->job == "")
      $this->c->replies->push("ko");
    else
      $this->c->replies->push("ok");
    $this->c->inventaire();
    $i++;
  }

  public function assignJob($id) {
    $this->c->broadcast($id . " job assigned:Peon");
    $this->c->wait++;
  }

  public function jobDispatch() {
    $this->c->state = "jobDispatch";
    while ($this->c->replies->getSize() > 0)
      $this->c->replies->pop();
    if ($this->c->bosscheck >= 3)
      {
	$this->c->job = "Boss";
	$this->c->replies->push("Boss");
	$this->c->bosscheck = 0;
	return;
      }
    switch ($this->c->job) {
    case "":
      $this->c->replies->push("Starter");
      break;
    case "Peon":
      $this->c->replies->push("Peon");
      break;
    case "Boss":
      $this->c->replies->push("Boss");
      break;
    case "Replicator":
      $this->c->replies->push("Replicator");
      break;
    case "Gatherer":
      $this->c->replies->push("Gatherer");
      break;
    case "Traveler":
      $this->c->replies->push("Traveler");
      break;
    case "Incanter":
      $this->c->replies->push("Incanter");
      break;
    }
  }

  public function checkForBoss() {
    static $i = 0;
    $this->c->state = "checkForBoss";
    if ($i >= 20 && $this->c->job != "Boss")
      {
	$this->c->broadcast($this->c->team . " Everything ok Boss ?");
	$this->c->bosscheck++;
	$i = 0;
      }
    else
      $this->c->replies->push("ok");
    if ($i >= 21)
      $i = 0;
    $i++;
  }
}