<?php

require_once('Socket.class.php');
require_once('ZappyIA.class.php');

class ZappyNET extends Socket
{
  private $replies;
  private $orders;
  private $team;
  private $ia;
  private $buffer = "";
  private $test = true;

  public function __construct($args) {
    parent::__construct($args['h'], $args['p']);
    $this->replies = new Queue();
    $this->orders = new Queue();
    $this->ia = new ZappyIA($args['n'], $this->orders, $this->replies);
  }

  /*
   ** Apellee pour savoir si on doit monitorer la socket en eciture
   ** retourne true ou false
   */
  public function readable() {
    return true;
  }

  /*
   ** Apellee pour savoir si on doit monitorer la socket en eciture
   ** retourne true ou false
   */
  public function writable() {
    return $this->orders->getSize() != 0;
  }

  /*
   ** Apellee quand on peut lire sur la socket
   */
  public function is_readable() {
    $this->test = true;
    if (($str = $this->read()) == false) {
      $this->close();
      echo "Disconnected\n";
    }
    else {
      if (strrpos($str, "\n") == (strlen($str) - 1))
	{
	  $this->buffer .= $str;
	  $str = explode("\n", $this->buffer);
	  foreach ($str as $reply)
	    $this->replies->push(trim($reply));
	  $this->buffer = "";
	}
      else {
	$this->buffer .= $str;
      }
    }
  }

  /*
   ** Apellee quand on peut ecrire sur la socket
   */
  public function is_writable() {
    if ($this->test)
      if ($this->write($this->orders->pop()) == false)
	$this->close();
    $this->test = false;
  }

  public function update() {
    $this->ia->update();
  }
}
?>