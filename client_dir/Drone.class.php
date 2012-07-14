<?php
class Drone
{
  private $c;

  public function __construct($connect) {
    $this->c = $connect;
  }

  /*
   ** Automation
   */

  public function getAutomatons() {
    return $this->c->automatons;
  }

  private function firstRun() {
    if ($this->c->i == 0)
      $this->c->voir();
    else if ($this->c->i == 1)
      $this->c->start();
  }
  
  public function automation() {
    if ($this->c->i <= 2)
      $this->firstRun();
    else if ($this->c->wait == 0)
      {
	$this->c->reply = $this->c->replies->pop();
	if ($this->c->state == "start")
	  {
	    while ($this->c->replies->getSize() > 0)
	      $this->c->replies->pop();
	    $this->c->reply = "start";
	  }
	if ($this->c->reply != "" && $this->c->reply[0] != '{')
	  {
	    if (!isset($this->c->actions[$this->c->state][$this->c->reply]))
	      {
		$this->c->state = "start";
		$this->c->job = "";
		while ($this->c->replies->getSize() > 0)
		  $this->c->replies->pop();
		$this->c->reply = "start";
	      }
	    eval($this->c->actions[$this->c->state][$this->c->reply]);
	  }
      }
    else if ($this->c->replies->peekNext() == "ok" || $this->c->replies->peekNext() == "ko")
      {
	$this->c->replies->pop();
	$this->c->wait--;
      }
    else if ($this->c->replies->peekFront() == "ok" || $this->c->replies->peekFront() == "ko")
      {
	$this->c->replies->unpush();
	$this->c->wait--;
      }
    $this->c->i++;
  }
}
?>