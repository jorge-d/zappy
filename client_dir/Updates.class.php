<?php

class Updates
{
  private $c;
  
  public function __construct($connect) {
    $this->c = $connect;
  }

  public function waitForUpdate() {
    if ($this->c->update <= 0)
      return false;
    return true;
  }

  public function updateViewOrInventory() {
    $this->c->reply = $this->c->replies->pop();
    if ($this->c->reply != "" && $this->c->reply[0] == '{')
      {
	if (strstr($this->c->reply, 'joueur') === false)
	  $this->updateInventory($this->c->reply);
	else
	  {
	    $this->c->view->update($this->c->reply);
	    $this->c->level = $this->c->view->getSight();
	  }
	$this->c->update--;
      }
    else 
      $this->c->replies->push($this->c->reply);
  }
  
  private function updateInventory() {
    $str = $this->c->reply;
    $str = str_replace('{', '', $str);
    $str = str_replace('}', '', $str);
    $c = explode(',', $str);
    foreach ($c as $units) {
      $units = explode(' ', trim($units));
      $this->c->inventory[$units[0]] = $units[1];
    }
  }
}
?>