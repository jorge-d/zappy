<?php
class Checks
{
  private $c;
  private $emergency;

  public function __construct($connect) {
    $this->c = $connect;
    $this->emergency = 0;
  }

  public function enoughFood() {
    $this->c->state = "enoughFood";
    if ($this->c->level < 4 && $this->c->inventory["nourriture"] > 12)
      $this->c->replies->push("ok");
    else if ($this->c->level >= 4 && $this->c->level < 6 && $this->c->inventory["nourriture"] > 25)
      $this->c->replies->push("ok");
    else if ($this->c->level >= 6 && $this->c->inventory["nourriture"] > 50)
      $this->c->replies->push("ok");
    if ($this->c->inventory["nourriture"] < 3)
      $this->c->replies->push("emergency");
    else
      $this->c->replies->push("ko");
    $this->c->inventaire();
  }

  public function elevationCheck() {
    $this->c->state = "elevationCheck";
    if ($this->c->level == 1
	&& $this->c->inventory["linemate"] >= 1)
      {
	$this->c->job = "Incanter";
	$this->c->replies->push("ok");
      }
    else
      $this->c->replies->push("ko");
  }

  public function checkLevel($expected) {
    $this->c->state = "checkLevel " . $expected;
    if ($this->c->level == $expected)
      $this->c->replies->push("ok");
    else
      $this->c->replies->push("ko");
    if ($this->c->level >= 2 && $this->c->job != "Boss")
      $this->c->job = "Gatherer";
    $this->c->inventaire();
    $this->c->voir();
  }

  public function itemHere($item) {
    $this->c->state = "itemHere " . $item;
    if ($this->c->inventory["nourriture"] < 3)
      {
	$this->c->replies->push("emergency");
	return;
      }
    if (in_array($item, $this->c->view->getElementsAt(0)) === true)
      $this->c->replies->push("ok");
    else
      $this->c->replies->push("ko");
    $this->c->inventaire();
  }

  public function selectNextStone() {
    static $i = 0;
    $this->c->state = "selectNextStone";
    switch ($this->c->level + $i) {
    case 1:
      if ($this->c->inventory["linemate"] <= 1)
	$this->c->replies->push("linemate");
      break;
    case 2:
      if ($this->c->inventory["sibur"] <= 1)
	$this->c->replies->push("sibur"); 
      else if ($this->c->inventory["deraumere"] <= 1)
	$this->c->replies->push("deraumere");
      else if ($this->c->inventory["linemate"] <= 1)
	$this->c->replies->push("linemate");
      break;
    case 3:
      if ($this->c->inventory["phiras"] <= 2)
	$this->c->replies->push("phiras");
      else if ($this->c->inventory["sibur"] <= 1)
	$this->c->replies->push("sibur");
      else if ($this->c->inventory["linemate"] <= 2)
	$this->c->replies->push("linemate");
      break;
    case 4:
      if ($this->c->inventory["phiras"] <= 1)
	$this->c->replies->push("phiras");
      else if ($this->c->inventory["sibur"] <= 2)
	$this->c->replies->push("sibur");
      else if ($this->c->inventory["deraumere"] <= 1)
	$this->c->replies->push("deraumere");
      else if ($this->c->inventory["linemate"] <= 1)
	$this->c->replies->push("linemate");
      break;
    case 5:
      if ($this->c->inventory["mendiane"] <= 3)
	$this->c->replies->push("mendiane");
      else if ($this->c->inventory["sibur"] <= 1)
	$this->c->replies->push("sibur");
      else if ($this->c->inventory["deraumere"] <= 2)
	$this->c->replies->push("deraumere");
      else if ($this->c->inventory["linemate"] <= 1)
	$this->c->replies->push("linemate");
      break;
    case 6:
      if ($this->c->inventory["phiras"] <= 1)
	$this->c->replies->push("phiras");
      else if ($this->c->inventory["sibur"] <= 3)
	$this->c->replies->push("sibur");
      else if ($this->c->inventory["deraumere"] <= 2)
	$this->c->replies->push("deraumere");
      else if ($this->c->inventory["linemate"] <= 1)
	$this->c->replies->push("linemate");
      break;
    case 7:
      if ($this->c->inventory["thystame"] <= 1)
	$this->c->replies->push("thystame");
      else if ($this->c->inventory["phiras"] <= 2)
	$this->c->replies->push("phiras");
      else if ($this->c->inventory["mendiane"] <= 2)
	$this->c->replies->push("mendiane");
      else if ($this->c->inventory["sibur"] <= 2)
	$this->c->replies->push("sibur");
      else if ($this->c->inventory["deraumere"] <= 2)
	$this->c->replies->push("deraumere");
      else if ($this->c->inventory["linemate"] <= 1)
	$this->c->replies->push("linemate");
      break;
    }
    if ($this->isStone() === true)
      $i = 0;
    else
      {
	$i++;
	if ($i > 0 && ($i + $this->c->level) < 8)
	  $this->c->checks->SelectNextStone();
	else if (($i + $this->c->level) >= 8)
	  {
	    $i = 0;
	    $this->getRandomStone();
	  }
      }
  }
  
  private function getRandomStone() {
    $i = rand(0, 5);
    switch ($i) {
    case 0:
      $this->c->replies->push("linemate");
      break;
    case 1:
      $this->c->replies->push("deraumere");
      break;
    case 2:
      $this->c->replies->push("sibur");
      break;
    case 3:
      $this->c->replies->push("mendiane");
      break;
    case 4:
      $this->c->replies->push("phiras");
      break;
    case 5:
      $this->c->replies->push("thystame");
      break;
    }
  }

  private function isStone() {
    $stone = $this->c->replies->peekFront();
    if ($stone == "thystame" || $stone == "deraumere"
	|| $stone == "phiras" || $stone == "sibur"
	|| $stone == "mendiane" || $stone == "linemate") 
      return true;
    else
      return false;
  }
  public function checkStone($stone) {
    $this->c->state = "checkStone";
    $set = array(
		 "nourriture" => 0,
		 "linemate"=> 0,
		 "deraumere" => 0,
		 "sibur" => 0,
		 "mendiane" => 0,
		 "phiras" => 0,
		 "thystame" => 0,
		 "joueur" => 0
		 );
   
    $floor = array_merge($set, array_count_values($this->c->view->getElementsAt(0)));
    if ($floor["joueur"] == 1
	&& $floor[$stone] >= 1)
      $this->c->replies->push($stone);
    else
      $this->c->replies->push("ko");
  }

  public function takeStone($stone) {
    $this->c->prendObjet($stone);
    $this->c->state = "takeStone";
  }

  public function dropNeededStones() {
    $this->c->job = "";
    $set = array(
		   "nourriture" => 0,
		   "linemate"=> 0,
		   "deraumere" => 0,
		   "sibur" => 0,
		   "mendiane" => 0,
		   "phiras" => 0,
		   "thystame" => 0
		   );
    $floor = array_merge($set, array_count_values($this->c->view->getElementsAt(0)));
    if ($this->c->inventory["nourriture"] < 4)
      {
    	$this->c->state = "dropNeededStones";
    	$this->c->replies->push("food");
    	$this->c->job = "Gatherer";
    	$this->c->inventaire();
    	$this->c->voir();
    	return;
      }
    switch ($this->c->level) {
    case 1:
      if ($floor["linemate"] < 1)
	$this->c->poseObjet("linemate");
      else
	$this->c->replies->push("ok");
      break;
    case 2:
      if ($floor["sibur"] < 1)
	$this->c->poseObjet("sibur"); 
      else if ($floor["deraumere"] < 1)
	$this->c->poseObjet("deraumere");
      else if ($floor["linemate"] < 1)
	$this->c->poseObjet("linemate");
      else
	$this->c->replies->push("ok");
      break;
    case 3:
      if ($floor["phiras"] < 2)
	$this->c->poseObjet("phiras");
      else if ($floor["sibur"] < 1)
	$this->c->poseObjet("sibur");
      else if ($floor["linemate"] < 2)
	$this->c->poseObjet("linemate");
      else
	$this->c->replies->push("ok");
      break;
    case 4:
      if ($floor["phiras"] < 1)
	$this->c->poseObjet("phiras");
      else if ($floor["sibur"] < 2)
	$this->c->poseObjet("sibur");
      else if ($floor["deraumere"] < 1)
	$this->c->poseObjet("deraumere");
      else if ($floor["linemate"] < 1)
	$this->c->poseObjet("linemate");
      else
	$this->c->replies->push("ok");
      break;
    case 5:
      if ($floor["mendiane"] < 3)
	$this->c->poseObjet("mendiane");
      else if ($floor["sibur"] < 1)
	$this->c->poseObjet("sibur");
      else if ($floor["deraumere"] < 2)
	$this->c->poseObjet("deraumere");
      else if ($floor["linemate"] < 1)
	$this->c->poseObjet("linemate");
      else
	$this->c->replies->push("ok");
      break;
    case 6:
      if ($floor["phiras"] < 1)
	$this->c->poseObjet("phiras");
      else if ($floor["sibur"] < 3)
	$this->c->poseObjet("sibur");
      else if ($floor["deraumere"] < 2)
	$this->c->poseObjet("deraumere");
      else if ($floor["linemate"] < 1)
	$this->c->poseObjet("linemate");
      else
	$this->c->replies->push("ok");
      break;
    case 7:
      if ($floor["thystame"] < 1)
	$this->c->poseObjet("thystame");
      else if ($floor["phiras"] < 2)
	$this->c->poseObjet("phiras");
      else if ($floor["mendiane"] < 2)
	$this->c->poseObjet("mendiane");
      else if ($floor["sibur"] < 2)
	$this->c->poseObjet("sibur");
      else if ($floor["deraumere"] < 2)
	$this->c->poseObjet("deraumere");
      else if ($floor["linemate"] < 1)
	$this->c->poseObjet("linemate");
      else
	$this->c->replies->push("ok");
      break;
    }
    $this->c->state = "dropNeededStones";
    if (($this->c->target > $this->c->id && $this->c->target != -1)
	|| sizeof($this->c->targets) > 0)
      $this->c->inventaire();
    $this->c->voir();
    $this->c->inventaire();
  }

  public function takeUselessStones() {
    if ((($this->c->target > $this->c->id && $this->c->target != -1)))
      {
    	$this->c->state = "takeUselessStones";
    	$this->c->replies->push("clean");
    	$this->c->voir();
    	return;
      }
    if ($this->c->level >= 4 && sizeof($this->c->targets) == 0)
      {
    	$this->c->state = "takeUselessStones";
    	$this->c->replies->push("clean");
    	$this->c->voir();
    	return;
      }
    $clean = 0;
    $set = array(
		   "nourriture" => 0,
		   "linemate"=> 0,
		   "deraumere" => 0,
		   "sibur" => 0,
		   "mendiane" => 0,
		   "phiras" => 0,
		   "thystame" => 0
		   );
    $floor = array_merge($set, array_count_values($this->c->view->getElementsAt(0)));
    switch ($this->c->level) {
    case 1:
      if ($floor["linemate"] > 1)
	$this->c->prendObjet("linemate");
      else if ($floor["deraumere"] > 0)
	$this->c->prendObjet("deraumere");
      else if ($floor["sibur"] > 0)
	$this->c->prendObjet("sibur"); 
      else if ($floor["phiras"] > 0)
	$this->c->prendObjet("phiras"); 
      else if ($floor["mendiane"] > 0)
	$this->c->prendObjet("mendiane"); 
      else if ($floor["thystame"] > 0)
	$this->c->prendObjet("thystame");
      else
	$clean = 1;
      break;
    case 2:
      if ($floor["linemate"] > 1)
	$this->c->prendObjet("linemate");
      else if ($floor["deraumere"] > 1)
	$this->c->prendObjet("deraumere");
      else if ($floor["sibur"] > 1)
	$this->c->prendObjet("sibur"); 
      else if ($floor["phiras"] > 0)
	$this->c->prendObjet("phiras"); 
      else if ($floor["mendiane"] > 0)
	$this->c->prendObjet("mendiane"); 
      else if ($floor["thystame"] > 0)
	$this->c->prendObjet("thystame");
      else
	$clean = 1;
      break;
    case 3:
      if ($floor["linemate"] > 2)
	$this->c->prendObjet("linemate");
      else if ($floor["deraumere"] > 0)
	$this->c->prendObjet("deraumere");
      else if ($floor["sibur"] > 1)
	$this->c->prendObjet("sibur"); 
      else if ($floor["phiras"] > 2)
	$this->c->prendObjet("phiras"); 
      else if ($floor["mendiane"] > 0)
	$this->c->prendObjet("mendiane"); 
      else if ($floor["thystame"] > 0)
	$this->c->prendObjet("thystame");
      else
	$clean = 1;
      break;
    case 4:
      if ($floor["linemate"] > 1)
	$this->c->prendObjet("linemate");
      else if ($floor["deraumere"] > 1)
	$this->c->prendObjet("deraumere");
      else if ($floor["sibur"] > 2)
	$this->c->prendObjet("sibur"); 
      else if ($floor["phiras"] > 1)
	$this->c->prendObjet("phiras"); 
      else if ($floor["mendiane"] > 0)
	$this->c->prendObjet("mendiane"); 
      else if ($floor["thystame"] > 0)
	$this->c->prendObjet("thystame");
      else
	$clean = 1;
      break;
    case 5:
      if ($floor["linemate"] > 1)
	$this->c->prendObjet("linemate");
      else if ($floor["deraumere"] > 2)
	$this->c->prendObjet("deraumere");
      else if ($floor["sibur"] > 1)
	$this->c->prendObjet("sibur"); 
      else if ($floor["phiras"] > 0)
	$this->c->prendObjet("phiras"); 
      else if ($floor["mendiane"] > 3)
	$this->c->prendObjet("mendiane"); 
      else if ($floor["thystame"] > 0)
	$this->c->prendObjet("thystame");
      else
	$clean = 1;
      break;
    case 6:
      if ($floor["linemate"] > 1)
	$this->c->prendObjet("linemate");
      else if ($floor["deraumere"] > 2)
	$this->c->prendObjet("deraumere");
      else if ($floor["sibur"] > 3)
	$this->c->prendObjet("sibur"); 
      else if ($floor["phiras"] > 1)
	$this->c->prendObjet("phiras"); 
      else if ($floor["mendiane"] > 0)
	$this->c->prendObjet("mendiane"); 
      else if ($floor["thystame"] > 0)
	$this->c->prendObjet("thystame");
      else
	$clean = 1;
      break;
    case 7:
      if ($floor["linemate"] > 1)
	$this->c->prendObjet("linemate");
      else if ($floor["deraumere"] > 2)
	$this->c->prendObjet("deraumere");
      else if ($floor["sibur"] > 2)
	$this->c->prendObjet("sibur"); 
      else if ($floor["phiras"] > 2)
	$this->c->prendObjet("phiras"); 
      else if ($floor["mendiane"] > 2)
	$this->c->prendObjet("mendiane"); 
      else if ($floor["thystame"] > 1)
	$this->c->prendObjet("thystame");
      else
	$clean = 1;
      break;

    }
    if ($clean == 1)
      $this->c->replies->push("clean");
    $this->c->state = "takeUselessStones";
    $this->c->voir();
  }

  public function elevationStoneCombination() {
    $this->c->state = "elevationStoneCombination";
    $set = array(
		 "nourriture" => 0,
		 "linemate"=> 0,
		 "deraumere" => 0,
		 "sibur" => 0,
		 "mendiane" => 0,
		 "phiras" => 0,
		 "thystame" => 0,
		 "joueur" => 0
		 );
    $floor = array_merge($set, array_count_values($this->c->view->getElementsAt(0)));
    switch ($this->c->level) {
    case 1:
      if ($floor["linemate"] == 1
	  && $floor["joueur"] == 1)
	$this->c->replies->push("ok");
      else
	$this->c->replies->push("ko");
      break;
    case 2:
      if ($floor["sibur"] == 1
	  && $floor["deraumere"] == 1
	  && $floor["linemate"] == 1
	  && $floor["joueur"] == 2)
	$this->c->replies->push("ok");
      else
	$this->c->replies->push("ko");      
      break;
    case 3:
      if ($floor["phiras"] == 2
	  && $floor["sibur"] == 1
	  && $floor["linemate"] == 2
	  && $floor["joueur"] == 2)
	$this->c->replies->push("ok");
      else
	$this->c->replies->push("ko");
      break;
    case 4:
      if ($floor["phiras"] == 1
	  && $floor["sibur"] == 2
	  && $floor["deraumere"] == 1
	  && $floor["linemate"] == 1
	  && $floor["joueur"] == 4)
	$this->c->replies->push("ok");
      else
	$this->c->replies->push("ko");
      break;
    case 5:
      if ($floor["mendiane"] == 3
	  && $floor["sibur"] == 1
	  && $floor["deraumere"] == 2
	  && $floor["linemate"] == 1
	  && $floor["joueur"] == 4)
	$this->c->replies->push("ok");
      else
	$this->c->replies->push("ko");
      break;
    case 6:
      if ($floor["phiras"] == 1
	  && $floor["sibur"] == 3
	  && $floor["deraumere"] == 2
	  && $floor["linemate"] == 1
	  && $floor["joueur"] == 6)
	$this->c->replies->push("ok");
      else
	$this->c->replies->push("ko");
      break;
    case 7:
      if ($floor["thystame"] == 1
	  && $floor["phiras"] == 2
	  && $floor["mendiane"] == 2
	  && $floor["sibur"] == 2
	  && $floor["deraumere"] == 2
	  && $floor["linemate"] == 1
	  && $floor["joueur"] == 6)
	$this->c->replies->push("ok");
      else
	$this->c->replies->push("ko");
      break;
    }
    $this->c->voir();
    $this->c->inventaire();
  }

  public function groupElevate() {
    if ($this->c->moves->playerCount() == true)
      $this->c->incantation();
    $this->c->state = "groupElevate";
    $this->c->job = "";
    $this->c->target = -1;
    $this->c->targets = array();
    $this->c->lastk = -1;
    $this->c->voir();
  }

  public function newEgg($alarm) {
    static $i = 0;
    $this->c->state = "newEgg";
    if ($alarm == 1)
      {
	$this->c->poseObjet("nourriture");
	$this->c->state = "newEgg";
	$this->emergency = 1;
      }
    if (((sizeof($this->c->team_id) <= sqrt($this->c->mapx * $this->c->mapy)
	 || sizeof($this->c->team_id) < 12)
	&& sizeof($this->c->team_id) < 15
	 && $i >= 5
	 && $this->emergency == 0))
      {
	$this->c->connectNbr();    
	$this->c->fork();
	$i = 0;
      }
    else
      $this->c->replies->push("ko");
    $i++;
    $this->c->voir();
  }

  public function checkConnect() {
    static $i = 0;
    static $forks = 0;
    $this->c->state = "checkConnect";
    if (((sizeof($this->c->team_id) <= sqrt($this->c->mapx * $this->c->mapy)
	 || sizeof($this->c->team_id) < 12)
	&& $i >= 5
	&& sizeof($this->c->team_id) < 15
	&& $this->c->clnb > 0)
	|| $this->emergency == 1)
      {
	$this->c->connectNbr();    
	$i = 0;
	$pid = pcntl_fork();
	if ($pid == -1)
	  {
	    $this->c->replies->push("ko");
	    return;
	  }
	else if ($pid == 0)
	  {
	    global $opts;
	    exec('php '.__DIR__.'/start.php -p '.$opts['p'].' -n '
		 .$opts['n'].' -h '.$opts['h']);
	    exit(0);
	  }
	$this->c->replies->push("ok");
      }
    else
      $this->c->replies->push("ko");
    $this->c->voir();
    $i++;
    $forks++;
  }
}
?>