<?php
class Automatons
{
  private $c;
  
  public function __construct($connect) {
   $this->c = $connect;
   $this->c->actions = array_merge ($this->BasicDrone(), $this->Starter(), $this->Peon(), $this->Boss(), $this->Replicator(), $this->Gatherer(), $this->Traveler(), $this->Incanter()); 
  }

  private function BasicDrone() {
    $automaton = array("start" => array("start" => '$this->c->checks->enoughFood();'),
		       "enoughFood" => array("ok" => '$this->c->jobs->checkForBoss();',
					     "emergency" => '$this->c->checks->newEgg(1);',
					     "ko" => '$this->c->checks->itemHere("nourriture");'),
		       "itemHere nourriture" => array("ok" => '$this->c->prendObjet("nourriture");',
						      "emergency" => '$this->c->checks->newEgg(1);',
						      "ko" => '$this->c->moves->moveTo("nourriture");'),
		       "moveTo nourriture" => array("ok" => '$this->c->checks->itemHere("nourriture");',
						    "ko" => '$this->c->checks->itemHere("nourriture");'),
		       "prend nourriture" => array("ok" => '$this->c->start();',
						   "ko" => '$this->c->start();'),
		       "checkForBoss" => array("ok" => '$this->c->jobs->jobDispatch();',
					       "ko" => '$this->c->jobs->jobDispatch();'),
		       "jobDispatch" => array("Starter" => '$this->c->broadcasts->sendId();',
					      "Peon" => '$this->c->checks->checkLevel(1);',
					      "Boss" => '$this->c->broadcasts->getGlobalStatus();',
					      "Replicator" => '$this->c->fork();',
					      "Gatherer" => '$this->c->checks->selectNextStone();',
					      "Traveler" => '$this->c->moves->travelTo();',
					      "Incanter" => '$this->c->checks->dropNeededStones();'
					      )
		       );
    return $automaton;
  }

  private function Starter() {
    $automaton = array (
			"sendId" => array("ok" => '$this->c->jobs->waitForJob();',
					  "ko" => '$this->c->start();'),
			"waitForJob" => array("ok" => '$this->c->start();',
					      "ko" => '$this->c->start();')
			);
    return $automaton;
  }

  private function Peon() {
    $automaton = array(
		       "checkLevel 1" => array("ok" => '$this->c->checks->elevationCheck();',
					       "ko" => '$this->c->start();'),
		       "elevationCheck" => array("ok" => '$this->c->start();',
						 "ko" => '$this->c->moves->gatherStone("linemate");')
		       );
    return $automaton;
  }

  private function Replicator() {
    $automaton = array (
			"fork" => array("ok" => '$this->c->connectNbr();',
					"ko" => '$this->c->start();')
			);
    return $automaton;
  }

  private function Boss() {
    $automaton = array (
			"getGlobalStatus" => array("ok" => '$this->c->broadcasts->sendOrders();',
						   "food" => '$this->c->start();',
						   "ko" => '$this->c->start();'),
			"sendOrders" =>  array("ok" => '$this->c->checks->newEgg(0);',
					       "ko" => '$this->c->broadcasts->sendOrders();',
					       "levelup" => '$this->c->checks->checkLevel(1);',
					       "food" => '$this->c->start();'),
			"newEgg" =>  array("ok" => '$this->c->checks->checkConnect();',
					   "food" => '$this->c->start();',
					   "ko" => '$this->c->checks->checkConnect();'),
			"checkConnect" =>  array("ok" => '$this->c->start();',
						 "food" => '$this->c->start();',
						 "ko" => '$this->c->start();')
			);
    return $automaton;
  }

  private function Gatherer() {
    $automaton = array (
			"selectNextStone" => array("linemate" => '$this->c->moves->gatherStone("linemate");',
						  "deraumere" =>'$this->c->moves->gatherStone("deraumere");',
						  "sibur" => '$this->c->moves->gatherStone("sibur");',
						  "mendiane" => '$this->c->moves->gatherStone("mendiane");',
						  "phiras" => '$this->c->moves->gatherStone("phiras");',
						  "thystame" => '$this->c->moves->gatherStone("thystame");'
						  ),
			"gatherStone" =>  array("linemate" => '$this->c->checks->checkStone("linemate");',
						"deraumere" =>'$this->c->checks->checkStone("deraumere");',
						"sibur" => '$this->c->checks->checkStone("sibur");',
						"mendiane" => '$this->c->checks->checkStone("mendiane");',
						"phiras" => '$this->c->checks->checkStone("phiras");',
						"thystame" => '$this->c->checks->checkStone("thystame");',
						"ok" => '$this->c->start();',
						"ko" => '$this->c->start();'
						),
			"checkStone" =>   array("linemate" => '$this->c->checks->takeStone("linemate");',
						"deraumere" =>'$this->c->checks->takeStone("deraumere");',
						"sibur" => '$this->c->checks->takeStone("sibur");',
						"mendiane" => '$this->c->checks->takeStone("mendiane");',
						"phiras" => '$this->c->checks->takeStone("phiras");',
						"thystame" => '$this->c->checks->takeStone("thystame");',
						"ko" => '$this->c->start();'
						),
			"takeStone" =>  array(
					      "ok" => '$this->c->start();',
					      "ko" => '$this->c->start();'
					      )
			);
    return $automaton;
  }

  private function Traveler() {
    $automaton = array (
			"travelTo" =>  array(
					     "ok" => '$this->c->moves->goToMeeting();',
					     "ko" => '$this->c->start();',
					     "food" => '$this->c->start();'
					     ),
			"goToMeeting" =>  array(
						"ok" => '$this->c->moves->travelTo();',
						"ko" => '$this->c->start();',
						"food" => '$this->c->start();',
						"arrived" => '$this->c->jobs->jobDispatch();'
						)
			);
    return $automaton;
  }

  private function Incanter() {
     $automaton = array (
			 "dropNeededStones" =>  array(
						      "ok" => '$this->c->checks->takeUselessStones();',
						      "ko" => '$this->c->checks->takeUselessStones();',
						      "food" => '$this->c->start();',
						      "clean" => '$this->c->checks->elevationStoneCombination();',
						      "elevation en cours" => '$this->c->checks->groupElevate();',
						      "niveau actuel : 2" => '$this->c->start();',
						      "niveau actuel : 3" => '$this->c->start();',
						      "niveau actuel : 4" => '$this->c->start();',
						      "niveau actuel : 5" => '$this->c->start();',
						      "niveau actuel : 6" => '$this->c->start();',
						      "niveau actuel : 7" => '$this->c->start();',
						      "niveau actuel : 8" => '$this->c->start();'
						      ),
			 "takeUselessStones" =>  array(
						       "ok" => '$this->c->checks->dropNeededStones();',
						       "ko" => '$this->c->checks->dropNeededStones();',
						       "food" => '$this->c->start();',
						       "clean" => '$this->c->checks->elevationStoneCombination();',
						       "elevation en cours" => '$this->c->checks->groupElevate();',
						       "niveau actuel : 2" => '$this->c->start();',
						       "niveau actuel : 3" => '$this->c->start();',
						       "niveau actuel : 4" => '$this->c->start();',
						       "niveau actuel : 5" => '$this->c->start();',
						       "niveau actuel : 6" => '$this->c->start();',
						       "niveau actuel : 7" => '$this->c->start();',
						       "niveau actuel : 8" => '$this->c->start();'
						       ),
			 "elevationStoneCombination" =>  array(
							       "ok" => '$this->c->checks->groupElevate();',
							       "ko" => '$this->c->checks->dropNeededStones();',
							       "food" => '$this->c->start();',
							       "clean" => '$this->c->checks->elevationStoneCombination();',
							       "elevation en cours" => '$this->c->checks->groupElevate();',
							       "niveau actuel : 2" => '$this->c->start();',
							       "niveau actuel : 3" => '$this->c->start();',
							       "niveau actuel : 4" => '$this->c->start();',
							       "niveau actuel : 5" => '$this->c->start();',
							       "niveau actuel : 6" => '$this->c->start();',
							       "niveau actuel : 7" => '$this->c->start();',
							       "niveau actuel : 8" => '$this->c->start();'
							       ),
			 "groupElevate" => array(
						 "ok" => '$this->c->checks->dropNeededStones();',
						 "ko" => '$this->c->checks->dropNeededStones();',
						 "food" => '$this->c->start();',
						 "clean" => '$this->c->checks->elevationStoneCombination();',
						 "elevation en cours" => '$this->c->checks->groupElevate();',
						 "niveau actuel : 2" => '$this->c->start();',
						 "niveau actuel : 3" => '$this->c->start();',
						 "niveau actuel : 4" => '$this->c->start();',
						 "niveau actuel : 5" => '$this->c->start();',
						 "niveau actuel : 6" => '$this->c->start();',
						 "niveau actuel : 7" => '$this->c->start();',
						 "niveau actuel : 8" => '$this->c->start();'
						 )
			);
    return $automaton;
 
  }
}
?>