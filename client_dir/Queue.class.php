<?php
class Queue
{
  private $queue;

  public function __construct() {
    $this->queue = array(); 
  }

  public function push($elem) {
    if ($elem != "")
      array_unshift($this->queue, $elem);
  }

  public function pop() {
    return array_pop($this->queue);
  }

  public function unpop($elem) {
    array_push($this->queue, $elem);
  }

  public function unpush() {
    return array_shift($this->queue);
  }

  public function is_full() {
    return true;
  }

  public function getSize() {
    return (sizeof($this->queue));
  }

  public function peekFront() {
    if (sizeof($this->queue) > 0)
      return $this->queue[0];
    else
      return -1;
  }

  public function peekNext() {
    if (sizeof($this->queue) > 0)
      return $this->queue[sizeof($this->queue) - 1];
    else
      return -1;
  }
}
?>