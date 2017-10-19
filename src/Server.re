type t = {ws: WebSocket.t};

type event =
  | ScanStarted
  | ScanFinished;

let serverUrl = "ws://localhost:8080";

let connect = (onConnect: t => unit, onEvent: event => unit) => {
  let ws = WebSocket.create_ws(serverUrl);
  WebSocket.onOpen(ws, () => onConnect({ws: ws}));
  WebSocket.onMsg(
    ws,
    (msg) =>
      switch msg {
      | "started" => onEvent(ScanStarted)
      | "finished" => onEvent(ScanFinished)
      | _ => Js.log("unknown message " ++ msg)
      }
  )
};

let startScanning = (server: t) => WebSocket.send(server.ws, "Scan!");