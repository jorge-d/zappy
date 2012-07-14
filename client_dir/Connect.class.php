<?php
require_once('Automatons.class.php');
require_once('Broadcasts.class.php');
require_once('Checks.class.php');
require_once('Jobs.class.php');
require_once('Moves.class.php');
require_once('Updates.class.php');
require_once('ViewingAngle.class.php');

class Connect
{
  public $orders;
  public $replies;
  public $inventory;
  public $actions;
  public $state;
  public $reply;
  public $update;
  public $wait;
  public $level;
  public $job;
  public $view;
  public $i;
  public $id;
  public $team_ids;
  public $team;
  public $global_status;
  public $target;
  public $targets;
  public $lastk;
  public $bosscheck;
  public $clnb;
  public $initial_clnb;
  public $mapx;
  public $mapy;

  public $automatons;
  public $broadcasts;
  public $checks;
  public $jobs;
  public $moves;
  public $updates;

  public function __construct($ord, $rep) {
    $this->automatons = new Automatons($this);
    $this->broadcasts = new Broadcasts($this);
    $this->checks = new Checks($this);
    $this->jobs = new Jobs($this);
    $this->moves = new Moves($this);
    $this->updates = new Updates($this);
    $this->view = new ViewingAngle();
    $this->orders = $ord;
    $this->replies = $rep;
    $this->update = 0;
    $this->reply = "";
    $this->update = 0;
    $this->wait = 0;
    $this->target = -1;
    $this->targets = array();
    $this->lastk = -1;
    $this->level = 1;
    $this->i = 0;
    $this->job = "";
    $this->bosscheck = 0;
    $this->clnb = 0;
    $this->initial_clnb = 0;
    $this->mapx = 0;
    $this->mapy = 0;
    $this->id = rand(0, 10000);
    $this->team = "";
    $this->team_id = array($this->id);
    $this->inventory = array("nourriture" => 10,
			     "linemate"=> 0,
			     "deraumere" => 0,
			     "sibur" => 0,
			     "mendiane" => 0,
			     "phiras" => 0,
			     "thystame" => 0);
  }

  public function avance() {
    $this->orders->push("avance\n");
    $this->wait++;
  }
  
  public function droite() {
    $this->orders->push("droite\n");
    $this->wait++;
  }
  
  public function gauche() {
    $this->orders->push("gauche\n");
    $this->wait++;
  }
  
  public function voir() {
    $this->orders->push("voir\n");
    $this->update++;
  }
  
  public function inventaire() {
    $this->orders->push("inventaire\n");
    $this->update++;
  }
  
  public function prendObjet($objet) {
    $this->state = "prend " . $objet;
    $this->orders->push("prend " . $objet . "\n");
    $this->inventaire();
    $this->voir();
  }
  
  public function poseObjet($objet) {
    $this->state = "pose " . $objet;
    $this->orders->push("pose " . $objet . "\n");
    $this->inventaire();
    $this->voir();
  }
  
  public function expulse() {
    $this->state = "expulse";
    $this->orders->push("expulse\n");
  }
  
  public function broadcast($texte) {
    $this->orders->push("broadcast " . $texte . "\n");
  }
  
  public function incantation() {
    $this->state = "incantation";
    $this->orders->push("incantation\n");
  }

  public function fork() {
    $this->orders->push("fork\n");
  }
      
  public function connectNbr() {
    $this->orders->push("connect_nbr\n");
  }

  public function start() { 
    $this->state = "start";
    while ($this->replies->getSize() > 0)
      $this->replies->pop();	
    $this->replies->push("start");
  }
}
?>