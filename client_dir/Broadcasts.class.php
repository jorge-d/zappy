<?php
class Broadcasts
{
  private $c;
  private $travel;

  public function __construct($connect) {
    $this->c = $connect;
  }

  private function followBroadcast($k)
  {
    if ($k == 1 || $k == 2 || $k == 8)
      $this->c->avance();
    else if ($k == 6 || $k == 7)
      $this->c->droite();
    else
      $this->c->gauche();
  }

  private function addTeammate ($message) {
    $id_team = explode("|", $message);
    if (in_array($id_team[0], $this->c->team_id) === false
	&& $id_team[1] == $this->c->team)
      {
	array_push($this->c->team_id, $id_team[0]);
	sort($this->c->team_id);
      }
  }
  private function selectTarget($message) {
    $messages = explode("|", $message);
    foreach ($messages as $meets) {
      if (strstr($meets, $this->c->id . ";"))
	{
	  $target = explode(";", $meets);
	  $this->c->target = trim($target[sizeof($target) - 1], ".");
	  if ($this->c->job != "Traveler" && $this->c->job != "Incanter" && $this->c->job != "")
	    {
	      $this->c->job = "Traveler";
	      $this->c->state = "start";
	    }
	  break;
	}
      else if (strstr($meets, $this->c->id . "."))
      	{
      	  $targets = explode(";", $meets);
	  $i = 0;
	  if (sizeof($targets) == 2)
	    $this->c->target = $targets[0];
	  else
	    foreach ($targets as $target) {
	      if ($target != $this->c->id)
		$this->c->targets[$i] = trim($target, ".");
	      $i++;
	    }
      	  if ($this->c->job != "Traveler" && $this->c->job != "Incanter" && $this->c->job != "")
      	    {
      	      $this->c->job = "Traveler";
	      $this->c->state = "start";
       	    }
      	  break;
      	}
    }
  }
  public function RegularInterpretBroadcast($broadcast) {
    $broadcast = substr($broadcast, 8);
    $a = explode(',', $broadcast);
    $k = $a[0];
    $message = $a[1];
    if (strstr($message, $this->c->id . " job assigned:") !== false)
      $this->c->job = trim(substr($message, strpos($message, ":") + 1));
    else if (strstr($message, $this->c->id . " come here") !== false && $this->c->job != "Incanter")
      {
	$this->c->lastk = $k;
	$this->c->job = "Traveler";
	if (($this->c->state == "travelTo" || $this->c->state == "goToMeeting"
	     || $this->c->state == "start") && sizeof($this->c->targets) == 0)
	  $this->c->replies->push("ok");
      }
    else if (strstr($message, "My id is :") !== false)
      $this->addTeammate(trim(substr($message, strpos($message, ":") + 1)));
    else if (strstr($message, $this->c->team . " Check status") !== false)
      $this->sendStatus();
    else if (strstr($message, "Meet:") !== false && $this->c->job != "Incanter")
      $this->selectTarget(trim(substr($message, strpos($message, ":") + 1)));
    else if (strstr($message, $this->c->team . " The Boss is Alive") !== false)
      $this->c->bosscheck = 0;
    else if (strstr($message, "Send me your id") !== false)
      {
	$this->c->broadcast("My id is :" . $this->c->id . "|" . $this->c->team);
	$this->wait++;
      }
  }

  public function BossInterpretBroadcast($broadcast) {
    $broadcast = substr($broadcast, 8);
    $a = explode(',', $broadcast);
    $k = $a[0];
    $message = $a[1];
    if (strstr($message, "My id is :") !== false)
      {
	$this->addTeammate(trim(substr($message, strpos($message, ":") + 1)));
	$this->c->jobs->assignJob(trim(substr($message, strpos($message, ":") + 1)));
      }
    else if (strstr($message, "Status:") !== false)
      $this->interpretStatus(trim(substr($message, strpos($message, ":") + 1)));
    else if (strstr($message, $this->c->team . " Everything ok Boss ?") !== false)
      {
	$this->c->broadcast($this->c->team . " The Boss is Alive");
	$this->c->wait++;
      }
    else if (strstr($message, $this->c->team . " Check status") !== false)
      {
	$this->c->job = "Peon";
	$this->c->state = "start";
	while ($this->c->replies->getSize() > 0)
	  $this->c->replies->pop();
      }
  }

  private function enoughRessourcesDuo($drone1, $drone2) {
    $mixed_inventory =  array("nourriture" => ($drone1["nourriture"] + $drone2["nourriture"]),
			      "linemate"=> ($drone1["linemate"] + $drone2["linemate"]),
			      "deraumere" => ($drone1["deraumere"] + $drone2["deraumere"]),
			      "sibur" => ($drone1["sibur"] + $drone2["sibur"]),
			      "mendiane" => ($drone1["mendiane"] + $drone2["mendiane"]),
			      "phiras" => ($drone1["phiras"] + $drone2["phiras"]),
			      "thystame" => ($drone1["thystame"] + $drone2["thystame"]));
    switch ($drone1["level"]) {
    case 2:
      if ($mixed_inventory["linemate"] >= 1 && $mixed_inventory["deraumere"] >= 1
	  && $mixed_inventory["sibur"] >= 1
	  && $mixed_inventory["nourriture"] >= 20)
	return true;
      return false;
    case 3:
      if ($mixed_inventory["linemate"] >= 2 && $mixed_inventory["phiras"] >= 2
	  && $mixed_inventory["sibur"] >= 1
	  && $mixed_inventory["nourriture"] >= 20)
	return true;
      return false;
    }
  }

  private function enoughRessourcesQuad($drone1, $drone2, $drone3, $drone4) {
    $mixed_inventory =  array("nourriture" => ($drone1["nourriture"] + $drone2["nourriture"] + $drone3["nourriture"] + $drone4["nourriture"]),
			      "linemate"=> ($drone1["linemate"] + $drone2["linemate"] + $drone3["linemate"] + $drone4["linemate"]),
			      "deraumere" => ($drone1["deraumere"] + $drone2["deraumere"] + $drone3["deraumere"] + $drone4["deraumere"]),
			      "sibur" => ($drone1["sibur"] + $drone2["sibur"] + $drone3["sibur"] + $drone4["sibur"]),
			      "mendiane" => ($drone1["mendiane"] + $drone2["mendiane"] + $drone3["mendiane"] + $drone4["mendiane"]),
			      "phiras" => ($drone1["phiras"] + $drone2["phiras"] + $drone3["phiras"] + $drone4["phiras"]),
			      "thystame" => ($drone1["thystame"] + $drone2["thystame"] + $drone3["thystame"] + $drone4["thystame"]));
    switch ($drone1["level"]) {
    case 4:
      if ($mixed_inventory["linemate"] >= 1 && $mixed_inventory["deraumere"] >= 1
	  && $mixed_inventory["sibur"] >= 2 && $mixed_inventory["phiras"] >= 1
	  && $mixed_inventory["nourriture"] >= 95)
	return true;
      return false;
    case 5:
      if ($mixed_inventory["linemate"] >= 1 && $mixed_inventory["deraumere"] >= 2
	  && $mixed_inventory["sibur"] >= 1 && $mixed_inventory["mendiane"] >= 3
	  && $mixed_inventory["nourriture"] >= 95)
	return true;
      return false;
    }
  }

  private function enoughRessourcesFinal($drone1, $drone2, $drone3, $drone4, $drone5, $drone6) {
    $mixed_inventory =  array("nourriture" => ($drone1["nourriture"] + $drone2["nourriture"] + $drone3["nourriture"] + $drone4["nourriture"]
					       + $drone5["nourriture"] + $drone6["nourriture"]),
			      "linemate"=> ($drone1["linemate"] + $drone2["linemate"] + $drone3["linemate"] + $drone4["linemate"]
					    + $drone5["linemate"] + $drone6["linemate"]),
			      "deraumere" => ($drone1["deraumere"] + $drone2["deraumere"] + $drone3["deraumere"] + $drone4["deraumere"]
					      + $drone5["deraumere"] + $drone6["deraumere"]),
			      "sibur" => ($drone1["sibur"] + $drone2["sibur"] + $drone3["sibur"] + $drone4["sibur"]
					  + $drone5["sibur"] + $drone6["sibur"]),
			      "mendiane" => ($drone1["mendiane"] + $drone2["mendiane"] + $drone3["mendiane"] + $drone4["mendiane"]
					     + $drone5["mendiane"] + $drone6["mendiane"]),
			      "phiras" => ($drone1["phiras"] + $drone2["phiras"] + $drone3["phiras"] + $drone4["phiras"]
					   + $drone5["phiras"] + $drone6["phiras"]),
			      "thystame" => ($drone1["thystame"] + $drone2["thystame"] + $drone3["thystame"] + $drone4["thystame"]
					     + $drone5["thystame"] + $drone6["thystame"]));
    switch ($drone1["level"]) {
    case 6:
      if ($mixed_inventory["linemate"] >= 1 && $mixed_inventory["deraumere"] >= 2
	  && $mixed_inventory["sibur"] >= 3 && $mixed_inventory["phiras"] >= 1
	  && $mixed_inventory["nourriture"] >= 280)
	return true;
      return false;
    case 7:
      if ($mixed_inventory["linemate"] >= 2 && $mixed_inventory["deraumere"] >= 2
	  && $mixed_inventory["sibur"] >= 2 && $mixed_inventory["mendiane"] >= 2
	  && $mixed_inventory["phiras"] >= 2 && $mixed_inventory["thystame"] >= 1
	  && $mixed_inventory["nourriture"] >= 280)
	return true;
      return false;
    }
  }

  private function meetDuo($meetings) {
    foreach ($this->c->team_id as $drone1) {
      foreach ($this->c->team_id as $drone2) {
	if ($drone1 != $drone2
	    && isset($this->c->global_status[$drone1]) && isset($this->c->global_status[$drone2]))
	  {
	    if ($this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone2]["level"]
		&& ($this->c->global_status[$drone1]["level"] == 2 || $this->c->global_status[$drone1]["level"] == 3)
		&& $this->c->global_status[$drone1]["job"] != "Traveler" && $this->c->global_status[$drone1]["job"] != "Incanter"
		&& $this->c->global_status[$drone2]["job"] != "Traveler" && $this->c->global_status[$drone2]["job"] != "Incanter")
	      {
		if ($this->enoughRessourcesDuo($this->c->global_status[$drone1], $this->c->global_status[$drone2]) === true
		    &&  strstr($meetings, $drone1 . "") === false
		    &&  strstr($meetings, $drone2 . "") === false
		    )
		  $meetings .= $drone1 . ";" . $drone2 . ".|";
		if ($drone1 == $this->c->id || $drone2 == $this->c->id)
		  $this->travel = 1;
	      }
	  }
      }
    }
    return ($meetings);
  }

  private function meetQuad($meetings) {
    foreach ($this->c->team_id as $drone1) {
      foreach ($this->c->team_id as $drone2) {
	foreach ($this->c->team_id as $drone3) {
	  foreach ($this->c->team_id as $drone4) {
	    if ($drone1 != $drone2 && $drone1 != $drone3 && $drone1 != $drone4 
		&& $drone2 != $drone3 && $drone2 != $drone4 && $drone3 != $drone4
		&& isset($this->c->global_status[$drone1]) && isset($this->c->global_status[$drone2])
		&& isset($this->c->global_status[$drone3]) && isset($this->c->global_status[$drone4]))
	      {
		if ($this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone2]["level"]
		    && $this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone3]["level"]
		    && $this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone4]["level"]
		    && ($this->c->global_status[$drone1]["level"] == 4 || $this->c->global_status[$drone1]["level"] == 5)
		    && $this->c->global_status[$drone1]["job"] != "Traveler" && $this->c->global_status[$drone1]["job"] != "Incanter"
		    && $this->c->global_status[$drone2]["job"] != "Traveler" && $this->c->global_status[$drone2]["job"] != "Incanter"
		    && $this->c->global_status[$drone3]["job"] != "Traveler" && $this->c->global_status[$drone3]["job"] != "Incanter"
		    && $this->c->global_status[$drone4]["job"] != "Traveler" && $this->c->global_status[$drone4]["job"] != "Incanter")
		  {
		    if ($this->enoughRessourcesQuad($this->c->global_status[$drone1], $this->c->global_status[$drone2],
						    $this->c->global_status[$drone3], $this->c->global_status[$drone4]) === true
			&&  strstr($meetings, $drone1 . "") === false
			&&  strstr($meetings, $drone2 . "") === false
			&&  strstr($meetings, $drone3 . "") === false
			&&  strstr($meetings, $drone4 . "") === false
			)
		      $meetings .= $drone1 . ";" . $drone2 . ";" . $drone3 . ";" . $drone4 . ".|";
		    if ($drone1 == $this->c->id || $drone2 == $this->c->id || $drone3 == $this->c->id || $drone4 == $this->c->id)
		      $this->travel = 1;
		  }
	      }
	  }
	}
      }
    }
    return ($meetings);
  }
  
  private function meetFinal($meetings) {
    foreach ($this->c->team_id as $drone1) {
      foreach ($this->c->team_id as $drone2) {
	foreach ($this->c->team_id as $drone3) {
	  foreach ($this->c->team_id as $drone4) {
	    foreach ($this->c->team_id as $drone5) {
	      foreach ($this->c->team_id as $drone6) {
		if ($drone1 != $drone2 && $drone1 != $drone3 && $drone1 != $drone4 && $drone1 != $drone5 && $drone1 != $drone6
		    && $drone2 != $drone3 && $drone2 != $drone4 && $drone2 != $drone5 && $drone2 != $drone6
		    && $drone3 != $drone4 && $drone3 != $drone5 && $drone3 != $drone6 && $drone4 != $drone5
		    && $drone4 != $drone6 && $drone5 != $drone6
		    && isset($this->c->global_status[$drone1]) && isset($this->c->global_status[$drone2])
		    && isset($this->c->global_status[$drone3]) && isset($this->c->global_status[$drone4])
		    && isset($this->c->global_status[$drone5]) && isset($this->c->global_status[$drone6]))
		  {
		    if ($this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone2]["level"]
			&& $this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone3]["level"]
			&& $this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone4]["level"]
			&& $this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone5]["level"]
			&& $this->c->global_status[$drone1]["level"] == $this->c->global_status[$drone6]["level"]
			&& ($this->c->global_status[$drone1]["level"] == 6 || $this->c->global_status[$drone1]["level"] == 7)
			&& $this->c->global_status[$drone1]["job"] != "Traveler" && $this->c->global_status[$drone1]["job"] != "Incanter"
			&& $this->c->global_status[$drone2]["job"] != "Traveler" && $this->c->global_status[$drone2]["job"] != "Incanter"
			&& $this->c->global_status[$drone3]["job"] != "Traveler" && $this->c->global_status[$drone3]["job"] != "Incanter"
			&& $this->c->global_status[$drone4]["job"] != "Traveler" && $this->c->global_status[$drone4]["job"] != "Incanter"
			&& $this->c->global_status[$drone5]["job"] != "Traveler" && $this->c->global_status[$drone5]["job"] != "Incanter"
			&& $this->c->global_status[$drone6]["job"] != "Traveler" && $this->c->global_status[$drone6]["job"] != "Incanter")
		      {
			if ($this->enoughRessourcesFinal($this->c->global_status[$drone1], $this->c->global_status[$drone2],
							 $this->c->global_status[$drone3], $this->c->global_status[$drone4],
							 $this->c->global_status[$drone5], $this->c->global_status[$drone6]) === true
			    &&  strstr($meetings, $drone1 . "") === false
			    &&  strstr($meetings, $drone2 . "") === false
			    &&  strstr($meetings, $drone3 . "") === false
			    &&  strstr($meetings, $drone4 . "") === false
			    &&  strstr($meetings, $drone5 . "") === false
			    &&  strstr($meetings, $drone6 . "") === false
			    )
			  $meetings .= $drone1 . ";" . $drone2 . ";" . $drone3 . ";" . $drone4 . ";" . $drone5 . ";" . $drone6 .".|";
			if ($drone1 == $this->c->id || $drone2 == $this->c->id || $drone3 == $this->c->id || $drone4 == $this->c->id
			    || $drone5 == $this->c->id || $drone6 == $this->c->id)
			  $this->travel = 1;
			return ($meetings);
		      }
		  }
	      }
	    }
	  }
	}
      }
    }
    return ($meetings);
  }

  private function countPlayersByLevel($lvl, $nb) {
    $i = 0;
    foreach ($this->c->team_id as $drone) {
      if (isset($this->c->global_status[$drone])
	  && $this->c->global_status[$drone]["level"] == $lvl)
	$i++;
      if (isset($this->c->global_status[$drone]) === false)
	  $this->c->team_id = array_diff($this->c->team_id, array($drone, ""));
    }
    if ($i >= $nb)
      return (true);
    return (false);
  }

  private function meetTeammate() {
      $meetings = "Meet:";
      $this->travel = 0;
      if ($this->countPlayersByLevel(2, 2) === true || $this->countPlayersByLevel(3, 2) === true)
	$meetings = $this->meetDuo($meetings);
      if ($this->countPlayersByLevel(4, 4) === true || $this->countPlayersByLevel(5, 4) === true)
	$meetings = $this->meetQuad($meetings);
      if ($this->countPlayersByLevel(6, 6) === true || $this->countPlayersByLevel(7, 6) === true)
	$meetings = $this->meetFinal($meetings);
      $this->c->global_status = array();
      $this->c->broadcast($meetings);
      if ($this->travel == 1)
	$this->selectTarget(trim(substr($meetings, strpos($meetings, ":") + 1)));
    }

    public function sendOrders() {
      static $i = 0;
      $this->c->state = "sendOrders";
      if ($this->c->level == 1)
	$this->c->replies->push("levelup");
      else if ($i == 1)
	$this->c->broadcast("Send me your id");
      else if ($this->c->inventory["nourriture"] <= 10)
      	$this->c->replies->push("food");
      else if (sizeof($this->c->global_status) >= 2 && $i == 15)
	$this->meetTeammate();
      else
	$this->c->replies->push("ok");
      if ($i > 15)
	$i = 0;
      else
	$i++;
      $this->c->inventaire();
    }

    public function sendId() {
      $this->c->state = "sendId";
      $this->c->broadcast("My id is :" . $this->c->id . "|" . $this->c->team);
    }

    public function isHappy() {
      $this->c->state = "isHappy";
      $this->c->broadcast($this->c->job . " number " . $this->c->id . " is Happy");
    }

    public function getGlobalStatus() {
      static $i = 0;
      $this->c->state = "getGlobalStatus";
      $this->c->global_status[$this->c->id] = array(
						    "level" => $this->c->level,
						    "job" => $this->c->job,
						    "nourriture" => $this->c->inventory["nourriture"],
						    "linemate" => $this->c->inventory["linemate"],
						    "deraumere" => $this->c->inventory["deraumere"],
						    "sibur" => $this->c->inventory["sibur"],
						    "mendiane" => $this->c->inventory["mendiane"],
						    "phiras" => $this->c->inventory["phiras"],
						    "thystame" => $this->c->inventory["thystame"]
						    );
      if ($i >= 10)
	{
	  $this->c->broadcast($this->c->team . " Check status");
	  $i = 0;
	}
      else
	$this->c->replies->push("ok");
      $this->c->inventaire();
      $i++;
    }

    private function sendStatus() {
      $this->c->broadcast("Status:" .
			  $this->c->id . "|" .
			  $this->c->level . "|" .
			  $this->c->job . "|" .
			  $this->c->inventory["nourriture"] . "|" .
			  $this->c->inventory["linemate"] . "|" .
			  $this->c->inventory["deraumere"] . "|" .
			  $this->c->inventory["sibur"] . "|" .
			  $this->c->inventory["mendiane"] . "|" .
			  $this->c->inventory["phiras"] . "|" .
			  $this->c->inventory["thystame"]
			  );
      $this->c->wait++;
    }
  
    private function interpretStatus($status) {
      $info = explode("|", $status);
      $this->addTeammate($info[0]);
      $this->c->global_status[$info[0]] = array(
						"level" => $info[1],
						"job" => $info[2],
						"nourriture" => $info[3],
						"linemate" => $info[4],
						"deraumere" => $info[5],
						"sibur" => $info[6],
						"mendiane" => $info[7],
						"phiras" => $info[8],
						"thystame" => $info[9]
						);
    }
  }
?>