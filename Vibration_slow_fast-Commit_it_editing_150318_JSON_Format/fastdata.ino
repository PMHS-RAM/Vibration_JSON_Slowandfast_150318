void fastdata() {

  get_timestamp();
  fifo_init();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  send_Fmsg();
}

