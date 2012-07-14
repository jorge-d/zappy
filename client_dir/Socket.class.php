<?php

abstract class Socket
{
  private $socket;
  private $read;
  private $write;
  private $callback = NULL;
  private $quit = false;

  public function __construct($ip, $port) {
    if (($this->socket =
	 socket_create(AF_INET, SOCK_STREAM, getprotobyname('tcp'))) == false)
      throw new Exception('Cannot create socket.');
    if (socket_connect($this->socket, $ip, $port) == false)
      throw new Exception(socket_strerror(socket_last_error($this->socket)));
  }

  public function __destruct() {
    socket_close($this->socket);
  }

  /*
   * Abstract methods
   */
  abstract public function readable();
  abstract public function writable();
  abstract public function is_readable();
  abstract public function is_writable();

  public function read() {
    if ($this->quit == false)
      return socket_read($this->socket, 1024);
    return 0;
  }

  public function write($str) {
    if ($this->quit == false)
      return socket_write($this->socket, $str);
    return 0;
  }

  public function setCallback($call) {
    $this->callback = $call;
  }

  public function close()
  {
    $this->quit = true;
  }

  public function monitor($tv_sec, $tv_usec = 0) {
    $cs = 0;
    $e = NULL;
    $time =  time();

    do {
      $this->read = array();
      $this->write = array();
      if ($this->readable())
	$this->read = array($this->socket);
      if ($this->writable())
	$this->write = array($this->socket);
      $cs = socket_select($this->read, $this->write, $e, $tv_sec, $tv_usec);
      if (is_array($this->read) && in_array($this->socket, $this->read))
	$this->is_readable();
      if ($this->quit == false
	  && is_array($this->write) && in_array($this->socket, $this->write))
	$this->is_writable();
      if ($this->callback && $this->quit == false && time() - $time >= $tv_sec)
	{
	  $this->{$this->callback}();
	  $time = time();
	}

    } while ($this->quit == false);
  }
}

?>